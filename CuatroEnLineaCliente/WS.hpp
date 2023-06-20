#ifndef MYWEBSOCKET_HPP
#define MYWEBSOCKET_HPP

#include <QObject>
#include <QWebSocket>
#include <QMutex>

enum {
    credencial = 0,
    board = 1

};

class MyWebSocket : public QObject
{
    Q_OBJECT

public:
    MyWebSocket(const QUrl &url, QObject *parent = nullptr);
    ~MyWebSocket();
    void sendBinaryMessage(const QByteArray &message);
    int getSessionId();

public slots:

    void onConnected();
    void onMessageReceived(const QByteArray &message);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket *m_webSocket;
    int session_id;
    QMutex m_mutex;
};

#endif // MYWEBSOCKET_HPP
