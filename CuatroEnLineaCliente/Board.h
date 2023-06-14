#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout *gridLayout;
};

#endif
