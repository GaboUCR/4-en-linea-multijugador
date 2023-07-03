#ifndef MYWEBSOCKET_HPP
#define MYWEBSOCKET_HPP

#include <QObject>
#include <QWebSocket>
#include <QMutex>
#include <QTimer>

/**
 * Enumeración para tipos de mensajes.
 */
// comunicación servidor-cliente
enum {
    credencial = 0,
    c_table = 5,
    c_board = 1,
    c_account = 2,
    c_logged = 3,
    c_not_logged = 4,
    c_begin_game = 6,
    c_game_won = 7,
    c_game_lost = 8,
    c_games = 9
};
// comunicación cliente-servidor
enum {
    board = 0,
    table = 1,
    nulo = 2,
    login = 3,
    signin = 4,
    gameWon = 5,
    gameLost = 6,
    gamesPlayed = 7
};


/**
 * @class MyWebSocket
 * @brief Clase que gestiona la comunicación WebSocket.
 *
 * Esta clase encapsula la funcionalidad necesaria para la comunicación a través de WebSockets,
 * permitiendo el envío y recepción de mensajes binarios y manteniendo la conexión viva mediante
 * un heartbeat.
 */
class MyWebSocket : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase MyWebSocket.
     * @param url URL del servidor WebSocket al que conectarse.
     * @param parent Puntero al objeto padre. Es nulo por defecto.
     */
    MyWebSocket(const QUrl &url, QObject *parent = nullptr);

    /**
     * @brief Destructor de la clase MyWebSocket.
     */
    ~MyWebSocket();

    /**
     * @brief Envía un mensaje binario a través del WebSocket.
     * @param message El mensaje a enviar.
     */
    void sendBinaryMessage(const QByteArray &message);

    /**
     * @brief Obtiene el ID de la sesión actual.
     * @return El ID de la sesión.
     */
    int getSessionId();

    QString getUsername();

    void setUsername(const QString &username);

signals:
    /**
     * @brief Señal emitida cuando el color de una celda del tablero cambia.
     * @param x Coordenada x de la celda.
     * @param y Coordenada y de la celda.
     * @param color El nuevo color de la celda.
     * @param id Identificador de la celda.
     */
    void boardColorChanged(int x, int y, int color, int id);

    /**
     * @brief Señal emitida para cambiar el turno.
     * @param isPlayer1Turn Indica si es el turno del jugador 1.
     */
    void changeTurn(bool isPlayer1Turn);

    /**
     * @brief Señal emitida cuando se recibe información de la cuenta.
     * @param username Nombre de usuario.
     * @param wins Número de victorias.
     * @param loss Número de derrotas.
     */
    void accountInfoReceived(const QString &username, int wins, int loss);

    /**
     * @brief Señal emitida cuando las credenciales son inválidas.
     */
    void invalidCredentials();

    /**
     * @brief Señal emitida cuando el usuario ha sido autenticado.
     */
    void userAuthenticated();

    /**
     * @brief Señal emitida para actualizar una mesa.
     * @param mesaNumber Número de mesa.
     * @param button Número de botón.
     * @param username Nombre de usuario.
     */
    void updateMesa(int mesaNumber, int button, const QString &username);

    /**
     * @brief Señal emitida cuando el juego comienza.
     * @param player1 Nombre del jugador 1.
     * @param player2 Nombre del jugador 2.
     * @param tableNumber Número de mesa.
     */
    void gameStarted(const QString& player1, const QString& player2, int tableNumber);

    /**
     * @brief Señal emitida cuando el juego termina.
     */
    void gameFinished();

    /**
     * @brief Señal emitida cuando se reciben las puntuaciones de los jugadores.
     * @param playersInfo Información de las puntuaciones de los jugadores.
     */
    void playerScoresReceived(const QList<QVariantMap>& playersInfo);



public slots:
    /**
     * @brief Slot llamado cuando la conexión WebSocket se establece.
     */
    void onConnected();

    /**
     * @brief Slot llamado cuando se recibe un mensaje a través del WebSocket.
     * @param message El mensaje recibido.
     */
    void onMessageReceived(const QByteArray &message);

    /**
     * @brief Slot llamado cuando la conexión WebSocket se cierra.
     */
    void onDisconnected();

    /**
     * @brief Slot llamado cuando ocurre un error en la conexión WebSocket.
     * @param error El error que ocurrió.
     */
    void onError(QAbstractSocket::SocketError error);

    /**
     * @brief Envía un heartbeat para mantener la conexión WebSocket viva.
     */
    void sendHeartbeat();

private:
    QWebSocket *m_webSocket;      /**< Puntero al objeto WebSocket. */
    int session_id;               /**< ID de la sesión actual. */
    QString m_username;           /**< Username de la sesión actual. */
    QMutex m_mutex;               /**< Mutex para sincronización. */
    QTimer* m_heartbeatTimer;     /**< Temporizador para enviar heartbeats. */
};

#endif // MYWEBSOCKET_HPP

