#ifndef SERVER_HPP
#define SERVER_HPP

#include <list>
#include <tuple>
#include <shared_mutex>
#include <string>
#include <boost/beast/websocket.hpp>

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

struct channel {
    std::shared_ptr<websocket::stream<tcp::socket>> session;
    int player_id;
    std::shared_mutex mutex;

};

struct GameTab {
    std::list<std::tuple<int, int>> tablero;
    int turno;
    std::tuple<int, int> jugadores;
    std::shared_mutex mutex;

};

struct TableTab {
    std::string jugador_1;
    std::string jugador_2;
    std::shared_mutex mutex;
};

enum {
    board = 0,
    table = 1
};

struct BoardMsg {
    int player_id;
    int table_id;
    int x;
    int y;
};

#endif // SERVER_HPP