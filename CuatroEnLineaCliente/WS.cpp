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

int MyWebSocket::getSessionId(){
    return session_id;
}

void MyWebSocket::onConnected()
{

    connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, &MyWebSocket::onMessageReceived);
    connect(m_webSocket, &QWebSocket::errorOccurred, this, &MyWebSocket::onError);

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

        // Obtener las partidas ganadas
        int wins = *reinterpret_cast<const int*>(message.constData() + 4 + 15);

        int loss = *reinterpret_cast<const int*>(message.constData() + 4 + 4 + 15);
        // Emitir la señal con la información de la cuenta
        emit accountInfoReceived(username, wins, loss);

    } else if (action == c_not_logged)
    {
        //emitir señal para mostrar mensaje en NavbarU
        emit invalidCredentials();
    }
}



void MyWebSocket::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "WebSocket error: " << error;
    qDebug() << "Error message: " << m_webSocket->errorString();
}

void MyWebSocket::onDisconnected()
{
    QMutexLocker locker(&m_mutex);
    // Stop the heartbeat timer when disconnected
    m_heartbeatTimer->stop();
    // Handle disconnection here
}
