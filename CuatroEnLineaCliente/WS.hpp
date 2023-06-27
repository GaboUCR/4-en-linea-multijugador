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
    c_board = 1,
    c_account = 2,
    c_logged = 3,
    c_not_logged = 4
};

// comunicación cliente-servidor
enum {
    board = 0,
    table = 1,
    nulo = 2,
    login = 3,
    signin = 4
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
     * @brief Señal emitida cuando el color de una casilla del tablero cambia.
     * @param x Coordenada x de la casilla.
     * @param y Coordenada y de la casilla.
     * @param color El nuevo color de la casilla.
     */
    void boardColorChanged(int x, int y, int color);

    /**
     * @brief Señal emitida para cambiar el turno.
     * @param isPlayer1Turn Indica si es el turno del jugador 1.
     */
    void changeTurn(bool isPlayer1Turn);

    void accountInfoReceived(const QString &username, int wins, int loss);
    void invalidCredentials();
    void userAuthenticated();

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
    QString m_username;
    QMutex m_mutex;               /**< Mutex para sincronización. */
    QTimer* m_heartbeatTimer;     /**< Temporizador para enviar heartbeats. */
};

#endif // MYWEBSOCKET_HPP

