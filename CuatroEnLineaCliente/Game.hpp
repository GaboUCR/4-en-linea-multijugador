#include <QWidget>
#include "WS.hpp"
#include "NavBarU.hpp"
#include "NavBarWidget.hpp"

/**
 * @class Game
 * @brief Clase que representa la interfaz y funcionalidad del juego.
 *
 * Esta clase maneja la interfaz y la lógica del juego, incluyendo la autenticación de usuarios
 * y el inicio de una partida.
 */
class Game : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase Game.
     * @param m_socket Puntero al objeto WebSocket para comunicación en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit Game(MyWebSocket* m_socket, QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot que se ejecuta cuando un usuario es autenticado.
     */
    void onUserAuthenticated();

    /**
     * @brief Slot que se ejecuta cuando el juego comienza.
     * @param player1 Nombre del primer jugador.
     * @param player2 Nombre del segundo jugador.
     * @param tableNumber Número de la mesa de juego.
     */
    void onGameStarted(const QString& player1, const QString& player2, int tableNumber);

private:
    NavBarU *m_navBarU;          /**< Puntero a la barra de navegación superior. */
    NavBarWidget *m_navBar;      /**< Puntero a la barra de navegación. */
    MyWebSocket *m_socket;       /**< Puntero al objeto WebSocket para comunicación en tiempo real. */
    QVBoxLayout *m_mainLayout;   /**< Layout principal del widget. */

signals:
    /**
     * @brief Señal que se emite cuando el juego termina.
     */
    void gameEnded();

public slots:
    /**
     * @brief Slot que permite al jugador volver al lobby.
     */
    void returnToLobby();
};
