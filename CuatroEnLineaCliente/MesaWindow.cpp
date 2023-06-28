// MesaWindow.cpp
#include "MesaWindow.hpp"
#include <QCheckBox>

MesaWindow::MesaWindow(MyWebSocket* m_socket, int mesaNumber, QWidget *parent) : QWidget(parent), m_socket(m_socket), mesaNumber(mesaNumber)
{
    // Setup layout
    layout = new QVBoxLayout(this);

    // Setup label with mesa number
    mesaLabel = new QLabel(QString("Mesa %1").arg(mesaNumber), this);
    layout->addWidget(mesaLabel);

    // Setup player buttons
    player1Button = new QPushButton(this);
    player2Button = new QPushButton(this);

    // Connect buttons to slots
    connect(player1Button, &QPushButton::clicked, this, &MesaWindow::onButtonClicked1);
    connect(player2Button, &QPushButton::clicked, this, &MesaWindow::onButtonClicked2);
    connect(m_socket, &MyWebSocket::updateMesa, this, &MesaWindow::onUpdateMesa);

    // Add buttons to layout
    layout->addWidget(player1Button);
    layout->addWidget(player2Button);
}

void MesaWindow::onButtonClicked1()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {

        QByteArray message;
        QDataStream stream(&message, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_15);
        stream.setByteOrder(QDataStream::LittleEndian);

        int tablev = table; // Coloca aquí el valor de la enumeración 'table'
        stream << tablev; // Añade el valor de la enumeración 'table' a la message

        // Añade el nombre del jugador, asegúrate de que tenga exactamente 15 bytes
        QString paddedUsername = m_socket->getUsername().leftJustified(15, ' ');
        stream.writeRawData(paddedUsername.toUtf8().data(), 15);

        int Id = m_socket->getSessionId();
        stream << Id; // Añadir el ID de la sesión

        int button = 1;
        stream << button; // Añadir el numero de botón

        stream << mesaNumber;

        // Envía el mensaje usando el WebSocket
        m_socket->sendBinaryMessage(message);
    }
}

void MesaWindow::onButtonClicked2()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {

        QByteArray message;
        QDataStream stream(&message, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_15);
        stream.setByteOrder(QDataStream::LittleEndian);

        int tablev = table; // Coloca aquí el valor de la enumeración 'table'
        stream << tablev; // Añade el valor de la enumeración 'table' a la message

        // Añade el nombre del jugador, asegúrate de que tenga exactamente 15 bytes
        QString paddedUsername = m_socket->getUsername().leftJustified(15, ' ');
        stream.writeRawData(paddedUsername.toUtf8().data(), 15);

        int Id = m_socket->getSessionId();
        stream << Id; // Añadir el ID de la sesión

        int button = 2;
        stream << button; // Añadir el numero de botón

        stream << mesaNumber;

        // Envía el mensaje usando el WebSocket
        m_socket->sendBinaryMessage(message);
    }
}

void MesaWindow::onUpdateMesa(int mesaNumber, int button, const QString &username) {
    if (mesaNumber == this->mesaNumber) {
        if (button == 1) {
            player1Button->setText(username);
            player1Button->setIcon(QIcon(":/checked.png"));

            if (username == "") {
                player1Button->setIcon(QIcon(":/unchecked.png"));
            }
        } else if (button == 2) {
            player2Button->setText(username);
            player2Button->setIcon(QIcon(":/checked.png"));

            if (username == "") {
                player2Button->setIcon(QIcon(":/unchecked.png"));
            }
        }
    }
}

