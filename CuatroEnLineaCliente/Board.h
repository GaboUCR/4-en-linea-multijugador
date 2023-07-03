#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include "WS.hpp"

/**
 * @enum ButtonColor
 * @brief Enumeración para representar los colores de los botones.
 */
enum ButtonColor {
    RED = 0, /**< Representa el color rojo. */
    YELLOW = 1 /**< Representa el color amarillo. */
};

/**
 * @class Board
 * @brief Clase que representa el tablero del juego.
 *
 * Esta clase es responsable de gestionar el tablero de juego.
 * Contiene una cuadrícula de botones y se encarga de cambiar el color de los botones.
 */
class Board : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase Board.
     * @param table_id Identificador de la mesa de juego.
     * @param socket Puntero al objeto websocket para comunicaciones en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    Board(int table_id, MyWebSocket* socket, QWidget *parent = nullptr);
    ~Board();

    /**
     * @brief Establece el WebSocket para comunicaciones en tiempo real.
     * @param m_socket Puntero al objeto websocket.
     */
    void SetWebSocket (MyWebSocket* m_socket);

signals:
    /**
     * @brief Señal emitida cuando un botón es presionado.
     * @param x Coordenada x del botón presionado.
     * @param y Coordenada y del botón presionado.
     * @param player_id Identificador del jugador que presionó el botón.
     * @param table_id Identificador de la mesa de juego.
     */
    void buttonClicked(int x, int y, int player_id, int table_id);

private slots:
    /**
     * @brief Manejador para cuando se presiona un botón.
     */
    void handleButtonClicked();

    /**
     * @brief Cambia el color de un botón en el tablero.
     * @param row Fila del botón.
     * @param col Columna del botón.
     * @param color Color del botón (enum ButtonColor).
     * @param id Identificador del botón.
     */
    void changeButtonColor(int row, int col, int color, int id);

protected:
    /**
     * @brief Maneja el evento de redimensionado del widget.
     * @param event Puntero al objeto QResizeEvent.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout *gridLayout;    /**< Layout en cuadrícula que contiene los botones. */
    QPushButton *buttons[7][7]; /**< Matriz de botones del tablero. */
    MyWebSocket* m_socket;      /**< Puntero al objeto WebSocket para comunicación en tiempo real. */
    int boardState[7][7];       /**< Estado del tablero de juego. */
    int boardColor[7][7];       /**< Color de los botones en el tablero. */
    int player_id;              /**< Identificador del jugador. */
    int table;                  /**< Identificador de la mesa de juego. */
    bool hasWon(int color, int lastMoveRow, int lastMoveCol); /**< Método para verificar si un jugador ha ganado. */
};

#endif // BOARD_H
