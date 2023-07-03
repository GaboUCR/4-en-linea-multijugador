#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include "WS.hpp"      // Incluir el archivo de cabecera de la clase MyWebSocket (si es necesario)

/**
 * @class GameWindow
 * @brief Clase que representa la ventana principal de juego.
 *
 * Esta clase gestiona la ventana principal de juego donde los jugadores compiten entre sí.
 */
class GameWindow : public QWidget {
public:
    /**
     * @brief Constructor de la clase GameWindow.
     * @param player1 Nombre del primer jugador.
     * @param player2 Nombre del segundo jugador.
     * @param tableNumber Número de la mesa de juego.
     * @param m_socket Puntero al objeto WebSocket para la comunicación en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    GameWindow(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* m_socket, QWidget* parent = nullptr);
};

#endif // GAME_WINDOW_HPP
