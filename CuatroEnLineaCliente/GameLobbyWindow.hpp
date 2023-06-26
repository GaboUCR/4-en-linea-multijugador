#ifndef GAMELOBBYWINDOW_HPP
#define GAMELOBBYWINDOW_HPP

#include <QMainWindow>
#include <QGridLayout>

class GameLobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameLobbyWindow(QWidget *parent = nullptr);

private:
    QGridLayout *gridLayout;
    QWidget *centralWidget;
};

#endif // GAMELOBBYWINDOW_HPP
