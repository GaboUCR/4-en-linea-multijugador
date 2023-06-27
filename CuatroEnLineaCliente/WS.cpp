#include "WS.hpp"
#include <QWebSocket>
#include <QUrl>
#include <QtNetwork>
#include <QMutex>
#include <QTimer>
#include <QMessageBox>


MyWebSocket::MyWebSocket(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_webSocket(new QWebSocket)

{
    connect(m_webSocket, &QWebSocket::connected, this, &MyWebSocket::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &MyWebSocket::onDisconnected);

    m_webSocket->open(url);

    // Create a new QTimer instance
    m_heartbeatTimer = new QTimer(this);
    // Connect the timer to the slot for sending the "heartbeat"
    connect(m_heartbeatTimer, &QTimer::timeout, this, &MyWebSocket::sendHeartbeat);
}

MyWebSocket::~MyWebSocket()
{
    m_heartbeatTimer->stop();
    delete m_heartbeatTimer;

    m_webSocket->close();
    delete m_webSocket;
}

void MyWebSocket::setUsername(const QString &username) {

    m_username = username;
}

QString MyWebSocket::getUsername(){

    return m_username;
}

int MyWebSocket::getSessionId(){

    return session_id;
}

void MyWebSocket::onConnected()
{

    connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, &MyWebSocket::onMessageReceived);
    connect(m_webSocket, &QWebSocket::errorOccurred, this, &MyWebSocket::onError);
    connect(m_webSocket, &QWebSocket::disconnected, this, &MyWebSocket::onDisconnected);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &MyWebSocket::onError);
    // Start the heartbeat timer to fire every 400ms
    m_heartbeatTimer->start(400);
}

void MyWebSocket::sendBinaryMessage(const QByteArray &message)
{
    QMutexLocker locker(&m_mutex);
    m_webSocket->sendBinaryMessage(message);
}

void MyWebSocket::sendHeartbeat()
{
    // The "heartbeat" is simply 4 bytes with a value of 2
    QByteArray heartbeat(4, 0);
    heartbeat[0] = 2;


    sendBinaryMessage(heartbeat);
}

void MyWebSocket::onMessageReceived(const QByteArray &message)
{
    QMutexLocker locker(&m_mutex);

    int action = *reinterpret_cast<const int*>(message.constData());

    if(action == credencial) // si los primeros 4 bytes son 0, sabemos que los siguientes 4 bytes son el ID de la sesión
    {
        this->session_id = *reinterpret_cast<const int*>(message.constData() + 4);


    } else if(action == table) // si los primeros 4 bytes son 1, tenemos un mensaje de cambio de color en el tablero
    {
        int x = *reinterpret_cast<const int*>(message.constData() + 4);
        int y = *reinterpret_cast<const int*>(message.constData() + 8);
        int color = *reinterpret_cast<const int*>(message.constData() + 12);

        emit boardColorChanged(x, y, color);
        emit changeTurn(color);

    } else if (action == c_logged)
    {
        // Suponiendo que el mensaje tiene la siguiente estructura:
        // [action(4 bytes), username(15 bytes), wins(4 bytes)]

        // Obtener el nombre de usuario
        const char* usernamePtr = message.constData() + 4;
        QString username = QString::fromUtf8(usernamePtr, 15).trimmed();
        this->m_username = username;

        // Obtener las partidas ganadas
        int wins = *reinterpret_cast<const int*>(message.constData() + 4 + 15);

        int loss = *reinterpret_cast<const int*>(message.constData() + 4 + 4 + 15);
        // Emitir la señal con la información de la cuenta
        emit accountInfoReceived(username, wins, loss);
        // Emitir la señal de autenticación del usuario
        emit userAuthenticated();

    } else if (action == c_not_logged)
    {
        //emitir señal para mostrar mensaje en NavbarU
        emit invalidCredentials();
    } else if (action == c_account)
    {
        // Obtener el nombre de usuario
        const char* usernamePtr = message.constData() + 4;
        QString username = QString::fromUtf8(usernamePtr, 15).trimmed();
        this->m_username = username;
        // Obtener las partidas ganadas
        int wins = *reinterpret_cast<const int*>(message.constData() + 4 + 15);

        int loss = *reinterpret_cast<const int*>(message.constData() + 4 + 4 + 15);
        // Emitir la señal con la información de la cuenta
        emit accountInfoReceived(username, wins, loss);
    }

}

void MyWebSocket::onError(QAbstractSocket::SocketError error)
{
    // Podemos mejorar la impresión de mensajes de error haciendo un switch en el tipo de error.
    qDebug() << "WebSocket encountered an error:";
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been acknowledged.";
        break;
    // ... Add cases for other types of errors ...
    default:
        qDebug() << "Error message: " << m_webSocket->errorString();
    }
}

void MyWebSocket::onDisconnected()
{
    // Detener el temporizador de latido al desconectarse
    m_heartbeatTimer->stop();

    // Imprimir un mensaje en la consola informando que el WebSocket se desconectó.
    qDebug() << "WebSocket disconnected.";
}

