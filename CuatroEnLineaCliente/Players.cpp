#include "Players.hpp"

Players::Players(const QString& player1, const QString& player2, int tableNumber, QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Players Window");

    layoutMain = new QGridLayout;

    tableLabel = new QLabel("Table: " + QString::number(tableNumber));

    player1Label = new QLabel(player1);
    player2Label = new QLabel(player2);

    player1PixmapLabel = new QLabel;
    player2PixmapLabel = new QLabel;

    QPixmap uncheckedPixmap(":/imagenes/unchecked.png");
    QPixmap checkedPixmap(":/imagenes/checked.png");

    player1PixmapLabel->setPixmap(checkedPixmap);
    player2PixmapLabel->setPixmap(uncheckedPixmap);

    // Ubicar los widgets en el grid layout
    layoutMain->addWidget(tableLabel, 0, 0, 1, 1);
    layoutMain->addWidget(player1PixmapLabel, 0, 1, 1, 1);
    layoutMain->addWidget(player1Label, 0, 2, 1, 1);
    layoutMain->addWidget(player2PixmapLabel, 0, 3, 1, 1);
    layoutMain->addWidget(player2Label, 0, 4, 1, 1);

    this->setLayout(layoutMain);
}
