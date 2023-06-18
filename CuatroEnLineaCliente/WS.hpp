#ifndef MYWEBSOCKET_HPP
#define MYWEBSOCKET_HPP

#include <QObject>
#include <QWebSocket>

class MyWebSocket : public QObject
{
    Q_OBJECT

public:
    MyWebSocket(const QUrl &url, QObject *parent = nullptr);
    ~MyWebSocket();
    void sendBinaryMessage(const QByteArray &message);

public slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &message);
    void onDisconnected();

private:
    QWebSocket *m_webSocket;
};

#endif // MYWEBSOCKET_HPP
