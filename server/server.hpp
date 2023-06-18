
#ifndef SERVER_HPP
#define SERVER_HPP

#include <list>
#include <tuple>
#include <shared_mutex>

struct GameTab {
    std::list<std::tuple<int, int>> tablero;
    int turno;
    std::tuple<int, int> jugadores;
    std::shared_mutex mutex;

};

enum {
    board = 0
};

struct BoardMsg {
    int player_id;
    int table_id;
    int x;
    int y;
};

#endif // SERVER_HPP