// MesaWindow.hpp
#ifndef MESAWINDOW_HPP
#define MESAWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "WS.hpp"

class MesaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MesaWindow(MyWebSocket* m_socket, int mesaNumber, QWidget *parent = nullptr);

private slots:
    void onButtonClicked1();
    void onButtonClicked2();

private:
    QLabel *mesaLabel;
    MyWebSocket *m_socket;
    QPushButton *player1Button;
    QPushButton *player2Button;
    QVBoxLayout *layout;
    int mesaNumber;
};

#endif // MESAWINDOW_HPP
