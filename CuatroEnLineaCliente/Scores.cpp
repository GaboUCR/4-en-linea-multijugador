#include "Scores.hpp"
#include "PlayerScore.hpp"
#include <QScrollArea>

Scores::Scores(MyWebSocket* m_socket, QWidget *parent) : QWidget(parent), m_socket(m_socket)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollAreaContent = new QWidget;

    gridLayout = new QGridLayout(scrollAreaContent);

    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollAreaContent);

    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);

    connect(m_socket, &MyWebSocket::playerScoresReceived, this, &Scores::updatePlayerScores);
}


void Scores::addPlayerScore(const QString &playerName, int wins, int losses)
{
    PlayerScore *playerScore = new PlayerScore(playerName, wins, losses, this);
    int row = gridLayout->rowCount();
    gridLayout->addWidget(playerScore, row, 0);
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
