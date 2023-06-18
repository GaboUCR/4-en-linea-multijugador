#include <boost/beast/core.hpp>
#include <boost/system/system_error.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <list>
#include <tuple>
#include "server.hpp"


using tcp = boost::asio::ip::tcp;       
namespace websocket = boost::beast::websocket;

void fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void do_session(tcp::socket socket, std::unordered_map<int, GameTab*>* games)
{
    try
    {
        // Create a websocket stream
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Accept the websocket handshake
        ws.accept();
        std::cout << "conexión aceptada" << std::endl;
        
        for(;;)
        {
            
            // Create a beast buffer
            boost::beast::flat_buffer buffer;

            // Read a message into the buffer
            ws.read(buffer);

            // Convert the buffer to bytes
            std::vector<uint8_t> bytes(buffers_begin(buffer.data()), buffers_end(buffer.data()));

            // Get the action type
            int action = *(int*)(bytes.data());

            // If action is board type
            if (action == 0) {

                // Create a BoardMsg instance
                BoardMsg board_msg;

                // Start from the 5th byte (index 4) because the first 4 bytes are for the action type

                board_msg.player_id = *(int*)(bytes.data() + 4);
                board_msg.table_id = *(int*)(bytes.data() + 8);
                board_msg.x = *(int*)(bytes.data() + 12);
                board_msg.y = *(int*)(bytes.data() + 16);

                // Print the board_msg data
                std::cout << "Player ID: " << board_msg.player_id << std::endl;
                std::cout << "Table ID: " << board_msg.table_id << std::endl;
                std::cout << "X: " << board_msg.x << std::endl;
                std::cout << "Y: " << board_msg.y << std::endl;

                // Now you can do whatever you want with board_msg
            }

            // Clear the buffer
            buffer.consume(buffer.size());


        }
    }
    catch(boost::beast::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << "\n";
        return;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return;
    }
}

int main()
{
    try
    {
        // Se inicializan los valores para los tableros
        std::unordered_map<int, GameTab*> games;

        for (int i=0; i<30; i++) {

            GameTab* gameTab = new GameTab;

            std::tuple<int, int> jugadores(-1, -1);
            std::list<std::tuple<int, int>> tablero;

            gameTab->jugadores = jugadores;
            gameTab->tablero = tablero;
            gameTab->turno = -1;

            games[i] = gameTab;

        }
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

            std::cout << "Cliente conectado \n";

            // Launch a new session for this connection
            std::thread(&do_session, std::move(socket), &games).detach();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
