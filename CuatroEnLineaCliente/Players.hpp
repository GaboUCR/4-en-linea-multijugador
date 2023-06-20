#ifndef PLAYERSWINDOW_H
#define PLAYERSWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

class Players : public QWidget
{
    Q_OBJECT

public:
    explicit Players(const QString& player1, const QString& player2, int tableNumber, QWidget *parent = nullptr);

private:
    QGridLayout *layoutMain;
    QLabel *tableLabel;
    QLabel *player1Label;
    QLabel *player2Label;
    QLabel *player1PixmapLabel;
    QLabel *player2PixmapLabel;
};

#endif // PLAYERSWINDOW_H
