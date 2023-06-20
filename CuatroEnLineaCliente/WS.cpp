#include "WS.hpp"
#include <QWebSocket>
#include <QUrl>
#include <QtNetwork>
#include <QMutex>

MyWebSocket::MyWebSocket(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_webSocket(new QWebSocket)

{
    connect(m_webSocket, &QWebSocket::connected, this, &MyWebSocket::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &MyWebSocket::onDisconnected);

    m_webSocket->open(url);
}

MyWebSocket::~MyWebSocket()
{
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
}

void MyWebSocket::sendBinaryMessage(const QByteArray &message)
{
    QMutexLocker locker(&m_mutex);
    m_webSocket->sendBinaryMessage(message);

}

void MyWebSocket::onMessageReceived(const QByteArray &message)
{
    QMutexLocker locker(&m_mutex);

    if(message.size() >= 8) // verificamos que el mensaje tenga al menos 8 bytes
    {
        int action = *reinterpret_cast<const int*>(message.constData());

        if(action == 0) // si los primeros 4 bytes son 0, sabemos que los siguientes 4 bytes son el ID de la sesión
        {
            session_id = *reinterpret_cast<const int*>(message.constData() + 4);
            qDebug() << "Session ID: " << session_id;
            // Aquí puedes emitir una señal o hacer lo que necesites con el ID de la sesión
        }
    }

    // Handle other binary messages here
}

void MyWebSocket::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "WebSocket error: " << error;
    qDebug() << "Error message: " << m_webSocket->errorString();
}

void MyWebSocket::onDisconnected()
{
    QMutexLocker locker(&m_mutex);
    // Handle disconnection here
}
