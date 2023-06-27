#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unordered_map>
#include <memory>
#include <tuple>
#include <list>
#include <thread>
#include <vector>
#include <shared_mutex>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <string>
#include <boost/beast/websocket.hpp>
#include "channel.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

// comunicación servidor-cliente
enum {
    credencial = 0,
    c_board = 1,
    c_account = 2,
    c_logged = 3,
    c_not_logged = 4
};
// comunicación cliente-servidor
enum {
    board = 0,
    table = 1,
    nulo = 2,
    login = 3,
    signin = 4
};


/**
 * @brief Estructura que representa el tablero de un juego.
 */
struct GameTab {
    std::tuple<int, int> jugadores;
    std::list<std::tuple<int, int>> tablero;
    int turno;
    std::shared_mutex mutex;
};

/**
 * @brief Estructura que representa la información de una mesa en el juego.
 */
struct TableTab {
    std::string jugador_1;
    std::string jugador_2;
    std::shared_mutex mutex;
};

/**
 * @brief Estructura que contiene la información de un mensaje de tablero.
 */
struct BoardMsg {
    int player_id;
    int table_id;
    int x;
    int y;
};

/**
 * @brief Función para reportar errores.
 * 
 * @param ec Código de error.
 * @param what Mensaje de error.
 */
void fail(boost::system::error_code ec, char const* what);

/**
 * @brief Función para cambiar el estado del tablero.
 * 
 * @param table_id ID de la mesa.
 * @param player_id ID del jugador.
 * @param x Coordenada x de la jugada.
 * @param y Coordenada y de la jugada.
 * @param sessions Mapa de sesiones.
 * @param games Mapa de juegos.
 */
void change_board(int table_id, int player_id, int x, int y, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games);

/**
 * @brief Función para manejar la sesión del cliente.
 * 
 * @param session_id ID de la sesión.
 * @param sessions Mapa de sesiones.
 * @param games Mapa de juegos.
 * @param tables Mapa de mesas.
 */
void do_session(int session_id, std::unordered_map<int, std::shared_ptr<channel>>& sessions, std::unordered_map<int, GameTab*>& games, std::unordered_map<int, TableTab*>& tables);

#endif // SERVER_HPP