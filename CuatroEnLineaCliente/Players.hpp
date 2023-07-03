#ifndef PLAYERSWINDOW_H
#define PLAYERSWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include "WS.hpp"

/**
 * @class Players
 * @brief Clase que representa la ventana de jugadores en el juego.
 *
 * Esta clase es responsable de gestionar la ventana que muestra información sobre los jugadores,
 * incluyendo sus nombres y turnos.
 */
class Players : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase Players.
     * @param player1 Nombre del primer jugador.
     * @param player2 Nombre del segundo jugador.
     * @param tableNumber Número de la mesa de juego.
     * @param m_socket Puntero al objeto WebSocket para comunicaciones en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    Players(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* m_socket, QWidget *parent = nullptr);

public slots:
    /**
     * @brief Cambia el indicador de turno entre los jugadores.
     * @param isPlayer1Turn Indica si es el turno del primer jugador.
     */
    void changeTurnIndicator(bool isPlayer1Turn);

protected:
    /**
     * @brief Maneja el evento de redimensionado de la ventana.
     * @param event Puntero al objeto QResizeEvent.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout *layoutMain;         /**< Layout principal que contiene los elementos de la ventana. */
    QLabel *tableLabel;              /**< Etiqueta para mostrar el número de la mesa. */
    QLabel *player1Label;            /**< Etiqueta para mostrar el nombre del primer jugador. */
    QLabel *player2Label;            /**< Etiqueta para mostrar el nombre del segundo jugador. */
    QLabel *player1PixmapLabel;      /**< Etiqueta para mostrar la imagen del primer jugador. */
    QLabel *player2PixmapLabel;      /**< Etiqueta para mostrar la imagen del segundo jugador. */
    QPixmap uncheckedPixmap;         /**< Imagen que representa cuando un jugador no tiene el turno. */
    QPixmap checkedPixmap;           /**< Imagen que representa cuando un jugador tiene el turno. */
    MyWebSocket* m_socket;           /**< Puntero al objeto WebSocket para comunicación en tiempo real. */
    int turn;                        /**< Variable para llevar el control del turno actual. */
    int oponent_id;                  /**< Identificador del oponente. */
};


#endif // PLAYERSWINDOW_H


