#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include "Players.hpp" // Incluir el archivo de cabecera de la clase Players
#include "Board.h"     // Incluir el archivo de cabecera de la clase Board
#include "WS.hpp"      // Incluir el archivo de cabecera de la clase MyWebSocket (si es necesario)

class GameWindow : public QWidget {
public:
    GameWindow(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* m_socket, QWidget* parent = nullptr);
};

#endif // GAME_WINDOW_HPP
