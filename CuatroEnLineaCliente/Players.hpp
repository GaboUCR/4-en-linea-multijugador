#ifndef PLAYERSWINDOW_H
#define PLAYERSWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include "WS.hpp"

class Players : public QWidget
{
    Q_OBJECT

public:
    Players(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* m_socket,  QWidget *parent = nullptr);

public slots:
    void changeTurnIndicator(bool isPlayer1Turn);

private:
    QGridLayout *layoutMain;
    QLabel *tableLabel;
    QLabel *player1Label;
    QLabel *player2Label;
    QLabel *player1PixmapLabel;
    QLabel *player2PixmapLabel;
    QPixmap uncheckedPixmap;
    QPixmap checkedPixmap;
    MyWebSocket* m_socket;
    int turn;
    int oponent_id;
};


#endif // PLAYERSWINDOW_H
