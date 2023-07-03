#include "GameLobbyWindow.hpp"
#include "MesaWindow.hpp"
#include <QScrollArea>
#include <QScrollBar>

GameLobbyWindow::GameLobbyWindow(MyWebSocket* m_socket, QWidget *parent) : QMainWindow(parent),
    m_socket(m_socket),
    centralWidget(new QWidget(this)),
    gridLayout(new QGridLayout(centralWidget))
{
    // Create 30 MesaWindow instances
    for (int i = 0; i < 30; ++i) {
        MesaWindow *mesaWindow = new MesaWindow(m_socket, i + 1);
        m_mesaWindows.append(mesaWindow); // Store MesaWindow pointers in a list
    }

    // Create a scroll area
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(centralWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(scrollArea);

    // Call resizeEvent initially to set the correct number of columns
    QSize initialSize = size();
    QResizeEvent initialResizeEvent(initialSize, initialSize);
    resizeEvent(&initialResizeEvent);
}

void GameLobbyWindow::resizeEvent(QResizeEvent *event)
{
    int windowWidth = event->size().width();
    int numColumns;

    // Set number of columns based on window width
    if (windowWidth >= 1000) {
        numColumns = 5;
    } else if (windowWidth >= 800) {
        numColumns = 4;
    } else if (windowWidth >= 600) {
        numColumns = 3;
    } else {
        numColumns = 2;
    }

    // Clear the layout
    while (gridLayout->count() > 0) {
        QLayoutItem *item = gridLayout->takeAt(0);
        item->widget()->setParent(nullptr);
    }

    // Add MesaWindow widgets back to the layout with new column count
    for (int i = 0; i < m_mesaWindows.size(); ++i) {
        MesaWindow *mesaWindow = m_mesaWindows.at(i);
        gridLayout->addWidget(mesaWindow, i / numColumns, i % numColumns);
    }
}
