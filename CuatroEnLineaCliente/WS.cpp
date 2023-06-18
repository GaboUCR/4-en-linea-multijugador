#include "WS.hpp"
#include <QWebSocket>
#include <QUrl>
#include <QtNetwork>

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

void MyWebSocket::onConnected()
{
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &MyWebSocket::onTextMessageReceived);
    connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, &MyWebSocket::onBinaryMessageReceived);
}

void MyWebSocket::sendBinaryMessage(const QByteArray &message)
{
    m_webSocket->sendBinaryMessage(message);
}

void MyWebSocket::onTextMessageReceived(const QString &message)
{
    // Handle text messages here
}

void MyWebSocket::onBinaryMessageReceived(const QByteArray &message)
{
    // Handle binary messages here
}

void MyWebSocket::onDisconnected()
{
    // Handle disconnection here
}
