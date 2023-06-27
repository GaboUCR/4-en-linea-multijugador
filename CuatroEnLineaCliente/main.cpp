#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStyle>
#include <QFont>
#include <QResizeEvent>
#include <QTimer>
#include <QWebSocket>
#include <QUrl>
#include <QtNetwork>
#include "Board.h"
#include "Players.hpp"
#include "GameLobbyWindow.hpp"
#include "Account.hpp"
#include "NavBarWidget.hpp"
#include "NavBarU.hpp"
#include "Game.hpp"


Board* ShowBoard(int table_id, MyWebSocket* socket) {
    Board *boardWindow = new Board(table_id, socket);
    boardWindow->setWindowTitle("Game Board");

    return boardWindow;
}

QWidget* ShowPlayers(const QString& player1, const QString& player2, int tableNumber, MyWebSocket *socket) {

    Players *playersWindow = new Players(player1, player2, tableNumber, socket);

    return playersWindow;
}

QWidget* ShowGameWindow(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* m_socket) {
    QWidget *gameWindow = new QWidget;
    gameWindow->setWindowTitle("Game Window");

    QVBoxLayout *layoutMain = new QVBoxLayout;

    QWidget* playersWidget = ShowPlayers(player1, player2, tableNumber, m_socket);
    Board* boardWidget = ShowBoard(2,m_socket);

    layoutMain->addWidget(playersWidget);
    layoutMain->addWidget(boardWidget);

    // Establecer las proporciones del espacio que cada widget debe tomar.
    layoutMain->setStretchFactor(playersWidget, 1);
    layoutMain->setStretchFactor(boardWidget, 3);

    gameWindow->setLayout(layoutMain);

    return gameWindow;
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QUrl url = QUrl("ws://localhost:8080");
    MyWebSocket *mySocket = new MyWebSocket(url);

    Game* e = new Game (mySocket);
    e -> show();

    return app.exec();
}
