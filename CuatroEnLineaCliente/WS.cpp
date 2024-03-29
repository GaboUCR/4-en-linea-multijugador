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

    connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, &MyWebSocket::onMessageReceived, Qt::DirectConnection);
    connect(m_webSocket, &QWebSocket::errorOccurred, this, &MyWebSocket::onError);
    connect(m_webSocket, &QWebSocket::disconnected, this, &MyWebSocket::onDisconnected);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred), this, &MyWebSocket::onError);

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

    // Crea un QDataStream a partir de QByteArray para poder especificar el endianness
    QDataStream dataStream(message);
    dataStream.setByteOrder(QDataStream::LittleEndian); // Establece little endian

    // Lee la acción
    int action;
    dataStream >> action;

    if(action == credencial)
    {
        // Lee el session_id como little endian
        dataStream >> this->session_id;
        qDebug() << this->session_id;
    }
    else if(action == c_board)
    {
        int x, y, color, id;
        // Lee x, y, y color como little endian
        dataStream >> x >> y >> color >> id;
        locker.unlock();
        emit boardColorChanged(x, y, color, id);
        emit changeTurn(color);
    }
    else if (action == c_logged || action == c_account)
    {
        // Lee el username
        char usernameChars[16];
        dataStream.readRawData(usernameChars, 15);
        usernameChars[15] = '\0'; // Null-terminar la cadena
        QString username = QString::fromUtf8(usernameChars).trimmed();

        // Lee las partidas ganadas y perdidas como little endian
        int wins, loss;
        dataStream >> wins >> loss;

        // Emitir la señal con la información de la cuenta
        emit accountInfoReceived(username, wins, loss);

        this->m_username = username;

        if (action == c_logged)
        {
            // Emitir la señal de autenticación del usuario
            emit userAuthenticated();
        }
    }
    else if (action == c_not_logged)
    {
        // Emitir señal para mostrar mensaje en NavbarU
        emit invalidCredentials();
    }
    else if (action == c_table) {
        // Lee el número de mesa
        int mesaNumero;
        dataStream >> mesaNumero;

        // Lee el valor del botón
        int button;
        dataStream >> button;

        // Lee el username
        char usernameChars[16];
        dataStream.readRawData(usernameChars, 15);
        usernameChars[15] = '\0';
        QString username = QString::fromUtf8(usernameChars).trimmed();

        qDebug() << username << "user";

        // Emitir la señal para actualizar la mesa
        emit updateMesa(mesaNumero, button, username);
    }
    else if (action == c_begin_game)
    {
        // Leer el número de mesa
        int tableNumber;
        dataStream >> tableNumber;

        // Leer los nombres de usuario
        char player1Chars[16];
        char player2Chars[16];
        dataStream.readRawData(player1Chars, 15);
        dataStream.readRawData(player2Chars, 15);
        player1Chars[15] = '\0'; // Null-terminar la cadena
        player2Chars[15] = '\0'; // Null-terminar la cadena
        QString player1 = QString::fromUtf8(player1Chars).trimmed();
        QString player2 = QString::fromUtf8(player2Chars).trimmed();

        // Emitir la señal de que el juego ha comenzado
        emit gameStarted(player1, player2, tableNumber);
    }
    else if (action ==  c_game_won || action == c_game_lost) {
        emit gameFinished();
    }
    else if (action == c_games) // Asegúrate de que c_games está definido correctamente como enum
    {
        // Lee la cantidad de jugadores como little endian
        int numPlayers;
        dataStream >> numPlayers;

        // Crea una lista para almacenar la información de cada jugador
        QList<QVariantMap> playersInfo;

        // Itera a través de cada jugador y lee su información
        for (int i = 0; i < numPlayers; i++)
        {
            // Lee el username
            char usernameChars[16];
            dataStream.readRawData(usernameChars, 15);
            usernameChars[15] = '\0'; // Null-terminar la cadena
            QString username = QString::fromUtf8(usernameChars).trimmed();

            // Lee el número de victorias y derrotas como little endian
            int wins, losses;
            dataStream >> wins >> losses;

            // Crea una estructura de datos para almacenar la información del jugador
            QVariantMap playerInfo;
            playerInfo["username"] = username;
            playerInfo["wins"] = wins;
            playerInfo["losses"] = losses;

            // Agrega la información del jugador a la lista
            playersInfo.append(playerInfo);
        }

        emit playerScoresReceived(playersInfo);

        // Imprimir la lista de información de los jugadores
        for (const QVariantMap &playerInfo : playersInfo) {
            qDebug() << "Username: " << playerInfo["username"].toString()
                     << ", Wins: " << playerInfo["wins"].toInt()
                     << ", Losses: " << playerInfo["losses"].toInt();
        }
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

