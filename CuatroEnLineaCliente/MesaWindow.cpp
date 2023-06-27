// MesaWindow.cpp
#include "MesaWindow.hpp"
#include <QCheckBox>

MesaWindow::MesaWindow(MyWebSocket* m_socket, int mesaNumber, QWidget *parent) : QWidget(parent), m_socket(m_socket)
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
    connect(player1Button, &QPushButton::clicked, this, &MesaWindow::onButtonClicked);
    connect(player2Button, &QPushButton::clicked, this, &MesaWindow::onButtonClicked);

    // Add buttons to layout
    layout->addWidget(player1Button);
    layout->addWidget(player2Button);
}

void MesaWindow::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {

        button->setText("Player Name"); // puedes establecer el nombre del jugador dinámicamente
        button->setIcon(QIcon(":/path/to/checked-checkbox.png")); // establece el icono de casilla marcada

        QByteArray message;
        int tablev = table; // Coloca aquí el valor de la enumeración 'table'

        // Añade el valor de la enumeración 'table' a la message
        message.append(reinterpret_cast<const char*>(&tablev), sizeof(tablev));

        // Añade el nombre del jugador, asegúrate de que tenga exactamente 15 bytes
        QString paddedUsername = m_socket->getUsername().leftJustified(15, ' ');
        message.append(paddedUsername.toUtf8());

        int Id = m_socket->getSessionId();

        // Añadir el ID de la sesión
        std::memcpy(message.data() + 4 + 15, &Id, 4);

        // Envía el mensaje usando el WebSocket
        m_socket->sendBinaryMessage(message);
    }
}
