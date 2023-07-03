#include "PlayerScore.hpp"

PlayerScore::PlayerScore(const QString &playerName, int wins, int losses, QWidget *parent) : QWidget(parent)
{
    playerNameLabel = new QLabel(playerName, this);
    winsLabel = new QLabel(QString("Wins: %1").arg(wins), this);
    lossesLabel = new QLabel(QString("Losses: %1").arg(losses), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(playerNameLabel);
    layout->addWidget(winsLabel);
    layout->addWidget(lossesLabel);

    setLayout(layout);
}
