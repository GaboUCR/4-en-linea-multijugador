#ifndef MYWEBSOCKET_HPP
#define MYWEBSOCKET_HPP

#include <QObject>
#include <QWebSocket>
#include <QMutex>
#include <QTimer>

enum {
    credencial = 0,
    c_board = 1

};

class MyWebSocket : public QObject
{
    Q_OBJECT

public:
    MyWebSocket(const QUrl &url, QObject *parent = nullptr);
    ~MyWebSocket();
    void sendBinaryMessage(const QByteArray &message);
    int getSessionId();

signals:
    void boardColorChanged(int x, int y, int color);
public slots:

    void onConnected();
    void onMessageReceived(const QByteArray &message);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void sendHeartbeat();

private:
    QWebSocket *m_webSocket;
    int session_id;
    QMutex m_mutex;
    QTimer* m_heartbeatTimer;
};

#endif // MYWEBSOCKET_HPP
