#include "GameLobbyWindow.hpp"
#include "MesaWindow.hpp"

GameLobbyWindow::GameLobbyWindow(MyWebSocket* m_socket ,QWidget *parent) : QMainWindow(parent)
{
    // Set up central widget and layout
    centralWidget = new QWidget(this);
    gridLayout = new QGridLayout(centralWidget);

    // Create 30 MesaWindow instances
    for (int i = 0; i < 30; ++i) {
        MesaWindow *mesaWindow = new MesaWindow(m_socket ,i + 1);
        gridLayout->addWidget(mesaWindow, i / 5, i % 5); // assuming 5 columns in the grid
    }

    setCentralWidget(centralWidget);
}
