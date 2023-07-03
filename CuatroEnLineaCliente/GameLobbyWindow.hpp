#ifndef GAMELOBBYWINDOW_HPP
#define GAMELOBBYWINDOW_HPP

#include "WS.hpp"
#include "MesaWindow.hpp"
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QResizeEvent>
#include <QList>

/**
 * @class GameLobbyWindow
 * @brief Clase que representa la ventana de la sala de espera del juego.
 *
 * Esta clase maneja la interfaz y la funcionalidad de la sala de espera del juego,
 * donde los jugadores pueden unirse a mesas de juego disponibles.
 */
class GameLobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase GameLobbyWindow.
     * @param m_socket Puntero al objeto WebSocket para la comunicación en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit GameLobbyWindow(MyWebSocket* m_socket, QWidget *parent = nullptr);

protected:
    /**
     * @brief Maneja el evento de redimensionado de la ventana.
     * @param event Puntero al objeto QResizeEvent.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    MyWebSocket* m_socket;          /**< Puntero al objeto WebSocket para la comunicación en tiempo real. */
    QWidget* centralWidget;         /**< Widget central en la ventana principal. */
    QGridLayout* gridLayout;        /**< Layout en cuadrícula para la disposición de elementos. */
    QList<MesaWindow*> m_mesaWindows; /**< Lista de ventanas de mesas de juego. */
};

#endif // GAMELOBBYWINDOW_HPP

