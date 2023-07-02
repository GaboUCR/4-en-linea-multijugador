#include "Scores.hpp"
#include "PlayerScore.hpp"
#include <QScrollArea>
#include <QButtonGroup>
#include <QPushButton>

Scores::Scores(MyWebSocket* m_socket, QWidget *parent) : QWidget(parent), m_socket(m_socket)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollAreaContent = new QWidget;

    gridLayout = new QGridLayout(scrollAreaContent);

    // Añadir un botón con una imagen
    QPushButton *button = new QPushButton(this);
    QIcon buttonIcon(":/imagenes/refresh.png"); // Reemplazar la ruta con la ruta de tu imagen
    button->setIcon(buttonIcon);
    button->setIconSize(QSize(100, 100)); // Cambiar el tamaño según tus necesidades
    connect(button, &QPushButton::clicked, this, &Scores::onButtonClicked); // Conectar la señal del botón clickeado

    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollAreaContent);

    // Agregar el botón y el área de desplazamiento al layout principal
    mainLayout->addWidget(button);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);

    connect(m_socket, &MyWebSocket::playerScoresReceived, this, &Scores::updatePlayerScores);
}

void Scores::onButtonClicked()
{
    QByteArray message;
    QDataStream stream(&message, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_15);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << (int) gamesPlayed;

    m_socket->sendBinaryMessage(message);
}

void Scores::addPlayerScore(const QString &playerName, int wins, int losses)
{
    PlayerScore *playerScore = new PlayerScore(playerName, wins, losses, this);
    int row = gridLayout->rowCount();
    gridLayout->addWidget(playerScore, row, 0, Qt::AlignCenter);
}

void Scores::updatePlayerScores(const QList<QVariantMap>& playersInfo)
{
    // Limpiar el layout antes de añadir nuevos widgets
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    // Añadir los widgets PlayerScore para cada jugador en la lista
    for (const QVariantMap &playerInfo : playersInfo) {
        QString username = playerInfo["username"].toString();
        int wins = playerInfo["wins"].toInt();
        int losses = playerInfo["losses"].toInt();

        addPlayerScore(username, wins, losses);
    }
}
