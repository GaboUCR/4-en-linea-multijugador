#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>

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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout *gridLayout;
    QPushButton *buttons[7][7];  // Aquí guardamos los punteros a los botones
};

#endif
