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
#include "channel.hpp"
#include <thread>
#include <chrono>
#include "DatabaseManager.hpp"

using tcp = boost::asio::ip::tcp;       
namespace websocket = boost::beast::websocket;

void fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void change_board(int table_id, int player_id, int x, int y, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games) {
    std::shared_lock<std::shared_mutex> game_lock(games[table_id]->mutex);

    // Comprobar si es el turno del jugador
    int current_turn = std::get<0>(games[table_id]->jugadores) == player_id ? 0 : 1;
    if (games[table_id]->turno != current_turn) {
        std::cout << "No es el turno del jugador " << player_id << std::endl;
        return;
    }

    // Comprobar si la jugada no ha sido realizada
    for (const auto& move : games[table_id]->tablero) {
        if (std::get<0>(move) == x && std::get<1>(move) == y) {
            std::cout << "La jugada ya ha sido realizada." << std::endl;
            return;
        }
    }

    // Añadir la jugada al tablero
    games[table_id]->tablero.emplace_back(x, y);

    // Cambiar el turno
    games[table_id]->turno = (games[table_id]->turno + 1) % 2;

    // Crear el mensaje
    std::vector<uint8_t> message(16, 0);
    *(int*)(message.data()) = c_board;
    *(int*)(message.data() + 4) = x;
    *(int*)(message.data() + 8) = y;
    *(int*)(message.data() + 12) = current_turn;  // color

    // Enviar el mensaje a ambos jugadores
    int player1_id = std::get<0>(games[table_id]->jugadores);
    int player2_id = std::get<1>(games[table_id]->jugadores);
    write_to_channel(*sessions[player1_id], message);
    write_to_channel(*sessions[player2_id], message);
}


void do_session(int session_id, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games, std::unordered_map<int, TableTab*>& tables)
{
    try
    {
        auto& ws = *(sessions[session_id]->session);
        auto dbManager  = new DatabaseManager("p.db");

        for (;;)
        {
            boost::beast::flat_buffer buffer;

            std::unique_lock<std::shared_mutex> lock(sessions[session_id]->mutex);
            ws.read(buffer);
            lock.unlock();

            std::vector<uint8_t> bytes(buffers_begin(buffer.data()), buffers_end(buffer.data()));

            int action = *(int*)(bytes.data());

            // If action is board type
            if (action == board) {

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

                // Aquí se llama change board
                change_board(board_msg.table_id, board_msg.player_id, board_msg.x, board_msg.y, sessions, games);
            }
            else if (action == signin)
            {
                std::string username(bytes.begin() + 4, bytes.begin() + 19);
                std::string password(bytes.begin() + 19, bytes.begin() + 39);

                username.erase(std::find_if(username.rbegin(), username.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), username.end());
                password.erase(std::find_if(password.rbegin(), password.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), password.end());

                std::vector<uint8_t> response;
                if (dbManager->registerPlayer(username, password))
                {
                    response.resize(4 + 15);
                    *(int*)response.data() = c_account; // successful registration
                    std::copy(username.begin(), username.end(), response.begin() + 4);
                }
                else
                {
                    response.resize(4);
                    *(int*)response.data() = c_not_logged; // failed registration
                }
                write_to_channel(*sessions[session_id], response);
            }
            else if (action == login)
            {
                std::string username(bytes.begin() + 4, bytes.begin() + 19);
                std::string password(bytes.begin() + 19, bytes.begin() + 39);

                username.erase(std::find_if(username.rbegin(), username.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), username.end());
                password.erase(std::find_if(password.rbegin(), password.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), password.end());

                std::vector<uint8_t> response;
                if (dbManager->authenticatePlayer(username, password))
                {
                    response.resize(4 + 15);
                    *(int*)response.data() = c_logged; // successful login
                    std::copy(username.begin(), username.end(), response.begin() + 4);
                }
                else
                {
                    response.resize(4);
                    *(int*)response.data() = c_not_logged; // failed login
                }
                write_to_channel(*sessions[session_id], response);
            }

            buffer.consume(buffer.size());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (boost::beast::system_error const& se)
    {
        if (se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << "\n";
        return;
    }
    catch (std::exception const& e)
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

        for (int i=1; i<31; i++) {

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

        // para el primer avance se va a utiliza la mesa 2, se debe borrar este codigo
        std::tuple<int, int> jugadores(0, 1);
        games[2]->jugadores = jugadores;
        games[2]->turno = 0;
        

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
        }            

        // Envía el ID de la sesión al cliente
        {
            std::unique_lock<std::shared_mutex> lock(sessions[session_id]->mutex);
            std::vector<uint8_t> message(8, 0); // crea un vector de 8 bytes, inicializado a 0
            *(int*)(message.data()) = 0; // los primeros 4 bytes son 0
            *(int*)(message.data() + 4) = session_id; // los siguientes 4 bytes son el id de la sesión
            boost::beast::flat_buffer buffer;
            buffer.commit(boost::asio::buffer_copy(buffer.prepare(message.size()), boost::asio::buffer(message)));
            sessions[session_id]->session->binary(true);
            sessions[session_id]->session->write(buffer.data());
        }

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
