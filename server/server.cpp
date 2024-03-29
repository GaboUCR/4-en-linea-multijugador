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
#include <climits>
#include <algorithm>
#include <random>

using tcp = boost::asio::ip::tcp;       
namespace websocket = boost::beast::websocket;

std::mutex sessions_mutex;  // Declara el mutex en un ámbito donde pueda ser accedido por los hilos relevantes

uint32_t toLittleEndian(uint32_t value) {
    static const int num = 1;
    if (*(char *)&num == 1) {
        // El sistema ya está en little endian, no es necesario cambiarlo
        return value;
    } else {
        // Convertir de big endian a little endian
        value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
        return (value << 16) | (value >> 16);
    }
}

void handleTableAction(std::string username, int button, int mesaNumero, int sessionId, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, TableTab*>& tables, std::unordered_map<int, GameTab*>& games, clickedTable* clicked) {
    // Actualizar los valores de la mesa
    bool escribir = false;
    {
        std::unique_lock<std::shared_mutex> lock(tables[mesaNumero]->mutex);
        if (button == 1) {
            
            if (tables[mesaNumero]->jugador_1 == "") {

                tables[mesaNumero]->jugador_1 = username;
                tables[mesaNumero]->id_1 = sessionId;
                clicked->clicked = mesaNumero;
                clicked->button = 1;
                escribir = true;
            } 
            else if (sessionId == tables[mesaNumero]->id_1) {
                tables[mesaNumero]->jugador_1 = "";
                tables[mesaNumero]->id_1 = -1;

                clicked->clicked = -1;
                clicked->button = -1;

                username = "";
                escribir = true;
            }

        } else if (button == 2) {

            if (tables[mesaNumero]->jugador_2 == "") {

                tables[mesaNumero]->jugador_2 = username;
                tables[mesaNumero]->id_2 = sessionId;

                clicked->clicked = mesaNumero;
                clicked->button = 2;   

                escribir = true;
            } 
            else if (sessionId == tables[mesaNumero]->id_2) {

                tables[mesaNumero]->jugador_2 = "";
                tables[mesaNumero]->id_2 = -1;

                clicked->clicked = -1;
                clicked->button = -1;

                username="";
                escribir = true;
            }
        }   
        
    }

    if (escribir) {
        // Crear el mensaje para enviar a los clientes
        std::vector<uint8_t> response(4 + 4 + 4 + 15);
        *(int*)response.data() = toLittleEndian(c_table); // los primeros 4 bytes son el enum c_table
        *(int*)(response.data() + 4) = toLittleEndian(mesaNumero); // los siguientes 4 bytes son el número de mesa
        *(int*)(response.data() + 8) = toLittleEndian(button); // los siguientes 4 bytes son el número del botón
        std::copy(username.begin(), username.end(), response.begin() + 12); // los siguientes 15 bytes son el nombre de usuario
        
        {    
            std::lock_guard<std::mutex> lock(sessions_mutex);
            // Enviar el mensaje a todos los clientes conectados
            for (auto& [session_id, session] : sessions) {
                write_to_channel(*session, response);
            }
        }
    }

    // Verificar si ambos jugadores están en la mesa y comenzar el juego si es así.
    bool start_game = false;
    {
        std::unique_lock<std::shared_mutex> lock(tables[mesaNumero]->mutex);
        if (!tables[mesaNumero]->jugador_1.empty() && !tables[mesaNumero]->jugador_2.empty()) {
            start_game = true;
        }
    }
    
    if (start_game) {
        // Crear un mensaje para informar a ambos jugadores que el juego ha comenzado.
        std::unique_lock<std::shared_mutex> lock(tables[mesaNumero]->mutex);
        int player1_session_id = tables[mesaNumero]->id_1;
        int player2_session_id = tables[mesaNumero]->id_2;

        std::string player1_name = tables[mesaNumero]->jugador_1;
        std::string player2_name = tables[mesaNumero]->jugador_2;

        // Rellenar los nombres de usuario con espacios para que tengan una longitud fija de 15
        player1_name.resize(15, ' ');
        player2_name.resize(15, ' ');

        uint32_t c_begin_gamev = c_begin_game;
        
        std::vector<uint8_t> game_start_message(4 + 4 + 15 + 15);
        *(uint32_t*)game_start_message.data() = toLittleEndian(c_begin_gamev); // los primeros 4 bytes son el enum c_begin_game
        *(uint32_t*)(game_start_message.data() + 4) = toLittleEndian(mesaNumero); // los siguientes 4 bytes son el número de mesa
        
        // Agregar los nombres de usuario al mensaje
        memcpy(game_start_message.data() + 8, player1_name.c_str(), 15);
        memcpy(game_start_message.data() + 8 + 15, player2_name.c_str(), 15);

        // Se inicializa el tablero de juego
        std::tuple<int, int> jugadores(player1_session_id, player2_session_id);
  
        games[mesaNumero]->jugadores = jugadores;
        games[mesaNumero]->turno = 0;
        
        // Enviar el mensaje de inicio del juego a los jugadores en la mesa.
        write_to_channel(*sessions[player1_session_id], game_start_message);
        write_to_channel(*sessions[player2_session_id], game_start_message);
    }


}

int fromLittleEndian(int value) {
    // Si la máquina es little-endian, no es necesario cambiar nada
    if (boost::endian::order::native == boost::endian::order::little) {
        return value;
    } 
    // Si es big-endian, cambiamos el orden de los bytes
    else {
        return ((value >> 24) & 0x000000FF) |
               ((value >> 8)  & 0x0000FF00) |
               ((value << 8)  & 0x00FF0000) |
               ((value << 24) & 0xFF000000);
    }
}

void fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void change_board(int table_id, int player_id, int x, int y, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games) {
    std::unique_lock<std::shared_mutex> game_lock(games[table_id]->mutex);

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
    std::vector<uint8_t> message(20, 0);
    *(int*)(message.data()) = toLittleEndian(c_board);
    *(int*)(message.data() + 4) = toLittleEndian(x);
    *(int*)(message.data() + 8) = toLittleEndian(y);
    *(int*)(message.data() + 12) = toLittleEndian(current_turn);
    *(int*)(message.data() + 16) = toLittleEndian(player_id);

    // Enviar el mensaje a ambos jugadores
    int player1_id = std::get<0>(games[table_id]->jugadores);
    int player2_id = std::get<1>(games[table_id]->jugadores);
    write_to_channel(*sessions[player1_id], message);
    write_to_channel(*sessions[player2_id], message);
}
 
void handle_win(int winner_session_id, int loser_session_id, int table_id ,std::unordered_map<int, std::shared_ptr<channel>>& sessions) {

    std::vector<uint8_t> win_message(4, 0);
    std::vector<uint8_t> lose_message(4, 0);

    // Pack the win and lose action codes
    *(int*)win_message.data() = toLittleEndian(c_game_won); // assuming c_game_won is an integer constant
    *(int*)lose_message.data() = toLittleEndian(c_game_lost); // assuming c_game_lost is an integer constant

    // Send win message to winner
    {
        std::unique_lock<std::shared_mutex> lock(sessions[winner_session_id]->mutex);
        boost::beast::flat_buffer buffer;
        buffer.commit(boost::asio::buffer_copy(buffer.prepare(win_message.size()), boost::asio::buffer(win_message)));
        sessions[winner_session_id]->session->binary(true);
        sessions[winner_session_id]->session->write(buffer.data());
    }
    
    // Send lose message to loser
    {
        std::unique_lock<std::shared_mutex> lock(sessions[loser_session_id]->mutex);
        boost::beast::flat_buffer buffer;
        buffer.commit(boost::asio::buffer_copy(buffer.prepare(lose_message.size()), boost::asio::buffer(lose_message)));
        sessions[loser_session_id]->session->binary(true);
        sessions[loser_session_id]->session->write(buffer.data());
    }
}

void printByteArray(const std::vector<unsigned char>& byteArray) {
    for (unsigned char byte : byteArray) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;  // Restaurar la base de impresión a decimal
}

void sendPlayerScores(int session_id, DatabaseManager& dbManager, std::unordered_map<int, std::shared_ptr<channel>>& sessions) {
    // Solicitar todos los registros de victorias y derrotas de la base de datos
    auto records = dbManager.getAllPlayersWinLossRecord();

    // Construir el mensaje de respuesta
    std::vector<uint8_t> response;
    int recordCount = records.size();

    // Reservar espacio en el vector: 4 (acción) + 4 (cantidad de jugadores) + 23 (username + victories + defeats) * cantidad de jugadores
    response.resize(4 + 4 + 23 * recordCount);

    // Escribir el tipo de acción y la cantidad de registros
    *(int*)response.data() = toLittleEndian(c_games);
    *(int*)(response.data() + 4) = toLittleEndian(recordCount);

    // Puntero para escribir cada registro en el mensaje
    uint8_t* recordPtr = response.data() + 8;

    // Escribir los registros en el mensaje
    for (const auto& [username, victories, defeats] : records)
    {
        // Copiar el username (max 15 bytes, completar con espacios)
        std::string paddedUsername = username;
        paddedUsername.resize(15, ' ');
        std::copy(paddedUsername.begin(), paddedUsername.end(), recordPtr);

        // Copiar las victorias y derrotas
        *(int*)(recordPtr + 15) = toLittleEndian(victories);
        *(int*)(recordPtr + 19) = toLittleEndian(defeats);

        // Mover el puntero al siguiente espacio para escribir
        recordPtr += 23;
    }

    // Enviar el mensaje construido
    write_to_channel(*sessions[session_id], response);
}

void do_session(int session_id, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games, std::unordered_map<int, TableTab*>& tables)
{

    clickedTable clicked_table;
    clicked_table.clicked = -1;
    clicked_table.button = -1;

    try
    {
        auto& ws = *(sessions[session_id]->session);

        DatabaseManager dbManager("p.db");

        sendPlayerScores(session_id, std::ref(dbManager), sessions);        

        for (;;)
        {
            boost::beast::flat_buffer buffer;

            ws.read(buffer);

            std::vector<uint8_t> bytes(buffers_begin(buffer.data()), buffers_end(buffer.data()));

            printByteArray(bytes);

            int action = boost::endian::little_to_native(*(reinterpret_cast<int*>(bytes.data())));

            // If action is board type
            if (action == board) {

                // Create a BoardMsg instance
                BoardMsg board_msg;

                // Start from the 5th byte (index 4) because the first 4 bytes are for the action type

                board_msg.player_id = fromLittleEndian(*(int*)(bytes.data() + 4));
                board_msg.table_id = fromLittleEndian(*(int*)(bytes.data() + 8));
                board_msg.x = fromLittleEndian(*(int*)(bytes.data() + 12));
                board_msg.y = fromLittleEndian(*(int*)(bytes.data() + 16));

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
                if (dbManager.registerPlayer(username, password))
                {
                    // Obtenemos las victorias y derrotas del usuario
                    auto [wins, losses] = dbManager.getPlayerWinLossRecord(username);
                    // Rellenar el nombre de usuario con espacios hasta llegar a 15 caracteres
                    username.resize(15, ' ');
                    
                    // Tamaño de la respuesta = 4 (acción) + 15 (nombre de usuario) + 4 (victorias) + 4 (derrotas)
                    response.resize(4 + 15 + 4 + 4);
                    *(int*)response.data() = toLittleEndian(c_logged);
                    *(int*)(response.data() + 4 + 15) = toLittleEndian(wins);
                    *(int*)(response.data() + 4 + 15 + 4) = toLittleEndian(losses);
                    std::copy(username.begin(), username.end(), response.begin() + 4);

                }
                else
                {
                    response.resize(4);
                    *(int*)response.data() = toLittleEndian(c_not_logged); // failed registration
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
                if (dbManager.authenticatePlayer(username, password))
                {

                    // Obtenemos las victorias y derrotas del usuario
                    auto [wins, losses] = dbManager.getPlayerWinLossRecord(username);

                    // Rellenar el nombre de usuario con espacios hasta llegar a 15 caracteres
                    username.resize(15, ' ');

                    response.resize(4 + 15 + 4 + 4);
                    *(int*)response.data() = toLittleEndian(c_logged);
                    *(int*)(response.data() + 4 + 15) = toLittleEndian(wins);
                    *(int*)(response.data() + 4 + 15 + 4) = toLittleEndian(losses);
                    std::copy(username.begin(), username.end(), response.begin() + 4);
                }
                else
                {
                    response.resize(4);
                    *(int*)response.data() = toLittleEndian(c_not_logged); // failed registration
                }
                write_to_channel(*sessions[session_id], response);
            } 
            else if (action == table) {
                // Leer el nombre del jugador que es de 15 bytes, empezando desde el índice 4.
                std::string username(bytes.begin() + 4, bytes.begin() + 4 + 15);

                // Eliminar espacios en blanco al final del nombre de usuario.
                username.erase(std::find_if(username.rbegin(), username.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), username.end());

                // Leer el ID de la sesión que es un entero de 4 bytes después del nombre del usuario.
                int sessionId = fromLittleEndian(*(int*)(bytes.data() + 4 + 15));

                // Leer el ID de la sesión que es un entero de 4 bytes después del nombre del usuario.
                int button = fromLittleEndian(*(int*)(bytes.data()+ 4 + 4 + 15));

                // Leer el numero de mesa 
                int mesaNumero = fromLittleEndian(*(int*)(bytes.data()+ 4 + 4 + 15 + 4));

                // Imprimir el mensaje en el servidor
                std::cout << "table" << mesaNumero  <<std::endl;
                std::cout << "button " << button  <<std::endl;
                std::cout << "Username: " << username << std::endl;
                std::cout << "Session ID: " << sessionId << std::endl;

                handleTableAction(username, button, mesaNumero, sessionId, sessions, tables, games, &clicked_table);

            }
            else if (action == gameWon) {
                // Leer los valores en el orden en que fueron enviados
                int colorv = fromLittleEndian(*(int*)(bytes.data() + 4));
                int tablev = fromLittleEndian(*(int*)(bytes.data() + 8));
                int sessionId = fromLittleEndian(*(int*)(bytes.data() + 12));

                // Mostrar los valores
                std::cout << "color: " << colorv << std::endl;
                std::cout << "table: " << tablev << std::endl;
                std::cout << "sessionId: " << sessionId << std::endl;
                
                int winner_session_id = sessionId;
                int loser_session_id;

                std::unique_lock<std::shared_mutex> game_lock(games[tablev]->mutex);
                std::string jugador_1 = tables[tablev]->jugador_1;
                int id_1 = tables[tablev]->id_1;

                std::string jugador_2 = tables[tablev]->jugador_2;
                int id_2 = tables[tablev]->id_2;
                game_lock.unlock();
                {
                    std::unique_lock<std::shared_mutex> game_lock(games[tablev]->mutex);

                    if (colorv == 0) {
                        loser_session_id = std::get<1>(games[tablev]->jugadores);

                        dbManager.incrementPlayerLosses(jugador_2);
                        dbManager.incrementPlayerWins(jugador_1);
                    } else {
                        loser_session_id = std::get<0>(games[tablev]->jugadores);
                        dbManager.incrementPlayerLosses(jugador_1);
                        dbManager.incrementPlayerWins(jugador_2);                        
                    }
                }

                // Obtenemos las victorias y derrotas del usuario 1
                auto [wins, losses] = dbManager.getPlayerWinLossRecord(jugador_1);

                std::vector<uint8_t> response;

                std::string username = jugador_1;

                // Rellenar el nombre de usuario con espacios hasta llegar a 15 caracteres
                username.resize(15, ' ');

                response.resize(4 + 15 + 4 + 4);
                *(int*)response.data() = toLittleEndian(c_account);
                *(int*)(response.data() + 4 + 15) = toLittleEndian(wins);
                *(int*)(response.data() + 4 + 15 + 4) = toLittleEndian(losses);
                std::copy(username.begin(), username.end(), response.begin() + 4);
                write_to_channel(*sessions[id_1], response);

                // Obtenemos las victorias y derrotas del usuario 2
                auto [wins_2, losses_2] = dbManager.getPlayerWinLossRecord(jugador_2);

                response.clear();
                username = jugador_2;

                // Rellenar el nombre de usuario con espacios hasta llegar a 15 caracteres
                username.resize(15, ' ');

                response.resize(4 + 15 + 4 + 4);
                *(int*)response.data() = toLittleEndian(c_account);
                *(int*)(response.data() + 4 + 15) = toLittleEndian(wins_2);
                *(int*)(response.data() + 4 + 15 + 4) = toLittleEndian(losses_2);
                std::copy(username.begin(), username.end(), response.begin() + 4);
                write_to_channel(*sessions[id_2], response);

                handle_win(winner_session_id, loser_session_id, tablev, sessions);
                    // Restablecer la entrada en 'games'
                    {   
                        std::unique_lock<std::shared_mutex> game_lock(games[tablev]->mutex);
                        games[tablev]->jugadores = std::make_tuple(-1, -1);
                        games[tablev]->tablero.clear(); // Limpiar la lista
                        games[tablev]->turno = -1;
                    }
                    // Restablecer la entrada en 'tables'
                    
                    handleTableAction(jugador_1, 1, tablev, id_1, sessions, tables, games, &clicked_table);
                    handleTableAction(jugador_2, 2, tablev, id_2, sessions, tables, games, &clicked_table);                   
            }
            else if (action == gamesPlayed)
            {
                sendPlayerScores(session_id, std::ref(dbManager), sessions);
            }
            
            buffer.consume(buffer.size());
        }
    }
    catch (boost::beast::system_error const& se)
    {
        // Cuando el WebSocket se cierra normalmente, no necesitamos imprimir un error.
        if (se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << "\n";
        else
            std::cerr << "WebSocket closed normally.\n";
        
        // Se elimina la sesión
        {
            std::lock_guard<std::mutex> lock(sessions_mutex);
            sessions.erase(session_id);
        }

        if (clicked_table.clicked != -1) {
            std::unique_lock<std::shared_mutex> lock(tables[clicked_table.clicked]->mutex);

            if (clicked_table.button == 1) {

                tables[clicked_table.clicked]->jugador_1 = "";
                tables[clicked_table.clicked]->id_1 = -1;
            }
            else {

                tables[clicked_table.clicked]->jugador_2 = "";
                tables[clicked_table.clicked]->id_2 = -1;

            }
            // Crear el mensaje para enviar a los clientes
            std::string username = "               ";
            std::vector<uint8_t> response(4 + 4 + 4 + 15);
            *(int*)response.data() = toLittleEndian(c_table); // los primeros 4 bytes son el enum c_table
            *(int*)(response.data() + 4) = toLittleEndian(clicked_table.clicked); // los siguientes 4 bytes son el número de mesa
            *(int*)(response.data() + 8) = toLittleEndian(clicked_table.button); // los siguientes 4 bytes son el número del botón
            std::copy(username.begin(), username.end(), response.begin() + 12); // los siguientes 15 bytes son el nombre de usuario
            
            {    
                std::lock_guard<std::mutex> lock(sessions_mutex);
                // Enviar el mensaje a todos los clientes conectados
                for (auto& [session_id, session] : sessions) {
                    write_to_channel(*session, response);
                }
            }

            {
                std::unique_lock<std::shared_mutex> lock(games[clicked_table.clicked]->mutex);

                // se deben liberar la partida si el jugador estaba jugando.
                if (games[clicked_table.clicked]->turno != -1) {
                    
                    int winner_id;

                    if( std::get<0>(games[clicked_table.clicked]->jugadores) == session_id)  {
                        
                        winner_id = std::get<1>(games[clicked_table.clicked]->jugadores);
                    }
                    else {
                        winner_id = std::get<0>(games[clicked_table.clicked]->jugadores);
                    }

                    std::vector<uint8_t> response_1(4);
                    *(int*)response.data() = toLittleEndian(c_game_won); // los primeros 4 bytes son el enum c_table


                    write_to_channel(*sessions[winner_id], response);
                }
                
                games[clicked_table.clicked]->jugadores = std::make_tuple(-1, -1);
                games[clicked_table.clicked]->tablero.clear(); // Limpiar la lista
                games[clicked_table.clicked]->turno = -1;


            }
            
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
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

            tableTab->id_1 = -1;
            tableTab->id_2 = -1;            

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
            std::lock_guard<std::mutex> lock(sessions_mutex);
            sessions[session_id] = new_channel;
        }            

        // Envía el ID de la sesión al cliente
        {
            std::unique_lock<std::shared_mutex> lock(sessions[session_id]->mutex);
            std::vector<uint8_t> message(8, 0); // crea un vector de 8 bytes, inicializado a 0
            *(int*)(message.data()) = 0; // los primeros 4 bytes son 0
            *(int*)(message.data() + 4) = toLittleEndian(session_id); // los siguientes 4 bytes son el id de la sesión
            boost::beast::flat_buffer buffer;
            buffer.commit(boost::asio::buffer_copy(buffer.prepare(message.size()), boost::asio::buffer(message)));
            sessions[session_id]->session->binary(true);
            sessions[session_id]->session->write(buffer.data());
        }

        // Enviar información de todas las mesas al cliente recién conectado
        
        // Enviar información de todas las mesas al cliente recién conectado
    for (int i = 1; i <= 30; i++) { // Asumiendo que hay 30 mesas numeradas de 1 a 30
        // Para el jugador 1
        {   
            std::unique_lock<std::shared_mutex> lock(tables[i]->mutex);
            std::vector<uint8_t> message;
            // Empaqueta la acción
            int action = toLittleEndian(c_table); // Suponiendo que c_table representa la acción de la mesa
            std::copy((uint8_t*)&action, (uint8_t*)&action + sizeof(action), std::back_inserter(message));

            // Empaqueta el número de mesa
            int mesaNumero = toLittleEndian(i);
            std::copy((uint8_t*)&mesaNumero, (uint8_t*)&mesaNumero + sizeof(mesaNumero), std::back_inserter(message));

            // Empaqueta la información del jugador 1
            int button1 = toLittleEndian(1);
            std::copy((uint8_t*)&button1, (uint8_t*)&button1 + sizeof(button1), std::back_inserter(message));
            std::string username1 = tables[i]->jugador_1;
            username1.resize(15, ' ');
            std::copy(username1.begin(), username1.end(), std::back_inserter(message));

            // Enviar mensaje al cliente
            std::unique_lock<std::shared_mutex> lock_s(sessions[session_id]->mutex);
            boost::beast::flat_buffer buffer;
            buffer.commit(boost::asio::buffer_copy(buffer.prepare(message.size()), boost::asio::buffer(message)));
            sessions[session_id]->session->binary(true);
            sessions[session_id]->session->write(buffer.data());
        
        }
        
        {
        
            // Para el jugador 2
            std::unique_lock<std::shared_mutex> lock(tables[i]->mutex);
            std::vector<uint8_t> message;
            // Empaqueta la acción
            int action = toLittleEndian(c_table); // Suponiendo que c_table representa la acción de la mesa
            std::copy((uint8_t*)&action, (uint8_t*)&action + sizeof(action), std::back_inserter(message));

            // Empaqueta el número de mesa
            int mesaNumero = toLittleEndian(i);
            std::copy((uint8_t*)&mesaNumero, (uint8_t*)&mesaNumero + sizeof(mesaNumero), std::back_inserter(message));

            // Empaqueta la información del jugador 2
            int button2 = toLittleEndian(2);
            std::copy((uint8_t*)&button2, (uint8_t*)&button2 + sizeof(button2), std::back_inserter(message));
            std::string username2 = tables[i]->jugador_2;
            username2.resize(15, ' ');
            std::copy(username2.begin(), username2.end(), std::back_inserter(message));

            // Enviar mensaje al cliente
            std::unique_lock<std::shared_mutex> lock_s(sessions[session_id]->mutex);
            boost::beast::flat_buffer buffer;
            buffer.commit(boost::asio::buffer_copy(buffer.prepare(message.size()), boost::asio::buffer(message)));
            sessions[session_id]->session->binary(true);
            sessions[session_id]->session->write(buffer.data());
        }
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
