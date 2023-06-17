#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket; // from <boost/beast/websocket.hpp>

void fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void do_session(tcp::socket socket)
{
    bool close = false;
    websocket::stream<tcp::socket> ws{std::move(socket)};

    boost::system::error_code ec;

    // Accept the websocket handshake
    ws.accept(ec);
    if(ec)
    {
        fail(ec, "accept");
        return;
    }

    while(!close)
    {
        // This buffer will hold the incoming message
        boost::beast::multi_buffer buffer;

        // Read a message
        ws.read(buffer, ec);
        if(ec)
        {
            fail(ec, "read");
            close = true;
        }

        // Echo the message back
        ws.text(ws.got_text());
        ws.write(buffer.data(), ec);
        if(ec)
        {
            fail(ec, "write");
            close = true;
        }
    }

    // Close the WebSocket connection
    ws.close(websocket::close_code::normal, ec);
    if(ec)
    {
        fail(ec, "close");
    }
}

int main()
{
    try
    {
        auto const address = boost::asio::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(std::atoi("8080"));

        // The io_context is required for all I/O
        boost::asio::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch a new session for this connection
            std::thread(&do_session, std::move(socket)).detach();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
