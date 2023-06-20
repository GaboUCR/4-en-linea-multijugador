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

void do_session(int session_id, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games, std::unordered_map<int, TableTab*>& tables)
{
    try
    {
        // Adquiere el bloqueo para esta sesión
        std::unique_lock<std::shared_mutex> lock(sessions[session_id]->mutex);

        // Creamos un puntero para el socket del websocket para facilitar su uso
        auto& ws = *(sessions[session_id]->session);

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

            // Libera el bloqueo antes de esperar para el siguiente mensaje
            lock.unlock();
            // Aquí podría poner alguna lógica de pausa o espera, si fuera necesario.
            lock.lock();
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
        // Se inicializan los valores compartidos para los tableros y las mesas
        std::unordered_map<int, GameTab*> games;
        std::unordered_map<int, TableTab*> tables;

        for (int i=0; i<30; i++) {

            GameTab* gameTab = new GameTab;
            
            std::tuple<int, int> jugadores(-1, -1);
            std::list<std::tuple<int, int>> tablero;

            gameTab->jugadores = jugadores;
            gameTab->tablero = tablero;
            gameTab->turno = -1;

            games[i] = gameTab;

            TableTab* tableTab = new TableTab;

            tableTab->jugador_1 = "";
            tableTab->jugador_2 = "";

            tables[i] = tableTab;
        }

        auto const address = boost::asio::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(std::atoi("8080"));

        std::cout << "¡Bienvenido al servidor de juegos!" << std::endl;
        std::cout << "El servidor está utilizando el puerto " << port << " para las conexiones." << std::endl;

        // The io_context is required for all I/O
        boost::asio::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};

        std::unordered_map<int, std::shared_ptr<channel>> sessions;
        std::shared_mutex sessions_mutex;
        int session_id = 0;

        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Create a websocket stream
            websocket::stream<tcp::socket> ws{std::move(socket)};
            
            // Accept the websocket handshake
            ws.accept();

            std::cout << "Cliente conectado \n";


            auto new_channel = std::make_shared<channel>();
            new_channel->session = std::make_shared<websocket::stream<tcp::socket>>(std::move(ws));
            // El mutex se inicializa automáticamente

            // Se agrega una nueva sesión
            {
                std::unique_lock<std::shared_mutex> lock(sessions_mutex);
                sessions[session_id] = new_channel;
                // El bloqueo se libera cuando sale del ámbito
            }            

            // se acepta la conexión

            // Launch a new session for this connection
            std::thread(&do_session, session_id, std::ref(sessions), std::ref(games), std::ref(tables)).detach();
            session_id++;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
