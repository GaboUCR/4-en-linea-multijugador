#include "Players.hpp"
#include "WS.hpp"
#include "qevent.h"

Players::Players(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* socket, QWidget *parent)
    : QWidget(parent), m_socket(socket)
{
    this->setWindowTitle("Players Window");

    layoutMain = new QGridLayout;

    layoutMain->setSpacing(5);

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

    connect(m_socket, &MyWebSocket::changeTurn, this, &Players::changeTurnIndicator);

    // llama a un evento de cambio de tamaño llamar el método resizeEvent
    QSize initialSize = size();
    QResizeEvent initialResizeEvent(initialSize, initialSize);
    resizeEvent(&initialResizeEvent);

    this->setLayout(layoutMain);
}

void Players::changeTurnIndicator(bool isPlayer1Turn) {
    QPixmap uncheckedPixmap(":/imagenes/unchecked.png");
    QPixmap checkedPixmap(":/imagenes/checked.png");

    if (isPlayer1Turn) {
        player1PixmapLabel->setPixmap(checkedPixmap);
        player2PixmapLabel->setPixmap(uncheckedPixmap);
    } else {
        player1PixmapLabel->setPixmap(uncheckedPixmap);
        player2PixmapLabel->setPixmap(checkedPixmap);
    }
}

//void Players::showEvent(QShowEvent *event)
//{
//    // Esto se llama cuando la ventana es mostrada
//    QWidget::showEvent(event); // llama a la implementación base
//}



void Players::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    int width = size.width();

    if (width < 400) {
        layoutMain->setContentsMargins(30, 2, 30, 2);

    } else if (width < 700) {
        layoutMain->setContentsMargins(60, 2, 60, 2);

    } else if (width < 800) {
        layoutMain->setContentsMargins(60, 10, 60, 10);

    } else if (width < 1000) {
        layoutMain->setContentsMargins(150, 10, 150, 10);

    } else if (width < 1200) {
        layoutMain->setContentsMargins(200, 10, 200, 10);

    } else if (width < 1400) {
        layoutMain->setContentsMargins(300, 10, 300, 10);

    } else {
        layoutMain->setContentsMargins(400, 10, 400, 10);
    }
}
