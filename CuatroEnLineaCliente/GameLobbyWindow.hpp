#ifndef GAMELOBBYWINDOW_HPP
#define GAMELOBBYWINDOW_HPP

#include <QMainWindow>
#include <QGridLayout>
#include "WS.hpp"

class GameLobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameLobbyWindow(MyWebSocket* m_socket,QWidget *parent = nullptr);

private:
    QGridLayout *gridLayout;
    QWidget *centralWidget;
    MyWebSocket * m_socket;
};

#endif // GAMELOBBYWINDOW_HPP
