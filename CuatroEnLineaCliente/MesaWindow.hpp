// MesaWindow.hpp
#ifndef MESAWINDOW_HPP
#define MESAWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "WS.hpp"

/**
 * @class MesaWindow
 * @brief Clase que representa la ventana de una mesa individual dentro de la sala de juego.
 *
 * Esta clase gestiona la ventana de una mesa de juego individual, permitiendo a los jugadores
 * unirse a la mesa y mostrar información sobre la mesa.
 */
class MesaWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase MesaWindow.
     * @param m_socket Puntero al objeto WebSocket para la comunicación en tiempo real.
     * @param mesaNumber Número identificador de la mesa.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit MesaWindow(MyWebSocket* m_socket, int mesaNumber, QWidget *parent = nullptr);

    // Indica si el jugador está ocupado.
    static bool isPlayerOccupied;

private slots:
    /**
     * @brief Manejador del evento de clic en el botón del jugador 1.
     */
    void onButtonClicked1();

    /**
     * @brief Manejador del evento de clic en el botón del jugador 2.
     */
    void onButtonClicked2();

    /**
     * @brief Actualiza la información de la mesa.
     * @param mesaNumber Número identificador de la mesa.
     * @param button Índice del botón (1 para jugador 1, 2 para jugador 2).
     * @param username Nombre de usuario del jugador que se ha unido.
     */
    void onUpdateMesa(int mesaNumber, int button, const QString &username);

private:
    QLabel *mesaLabel;          /**< Etiqueta para mostrar el número de la mesa. */
    MyWebSocket *m_socket;      /**< Puntero al objeto WebSocket para la comunicación en tiempo real. */
    QPushButton *player1Button; /**< Botón para el jugador 1. */
    QPushButton *player2Button; /**< Botón para el jugador 2. */
    QVBoxLayout *layout;        /**< Layout vertical para organizar los widgets. */

    int mesaNumber;             /**< Número identificador de la mesa. */
};

#endif // MESAWINDOW_HPP
