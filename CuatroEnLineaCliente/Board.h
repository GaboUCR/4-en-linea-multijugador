#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include "WS.hpp"

enum ButtonColor {
    RED,
    YELLOW
};

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    void changeButtonColor(int row, int col, ButtonColor color);

signals:
    void buttonClicked(int x, int y, int player_id, int table_id);

private slots:
    void handleButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout *gridLayout;
    QPushButton *buttons[7][7];  // Aquí guardamos los punteros a los botones
    MyWebSocket* m_socket;
    int player_id;
    int table;
};

#endif
