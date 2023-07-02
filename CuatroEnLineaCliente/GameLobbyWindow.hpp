#ifndef GAMELOBBYWINDOW_HPP
#define GAMELOBBYWINDOW_HPP

#include "WS.hpp"
#include "MesaWindow.hpp"
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QResizeEvent>
#include <QList>

class GameLobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameLobbyWindow(MyWebSocket* m_socket, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    MyWebSocket* m_socket;
    QWidget* centralWidget;
    QGridLayout* gridLayout;
    QList<MesaWindow*> m_mesaWindows;
};

#endif // GAMELOBBYWINDOW_HPP

