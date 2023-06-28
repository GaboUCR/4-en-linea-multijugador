#include "Game.hpp"
#include <QVBoxLayout>
#include "GameWindow.hpp"

Game::Game(MyWebSocket* m_socket, QWidget *parent)
    : QWidget(parent), m_socket(m_socket)
{
    m_navBarU = new NavBarU(m_socket);
    m_navBar = new NavBarWidget(m_socket); // Asumiendo que NavBar es similar a NavBarU

    // Layout principal
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_navBarU);

    // Conectar la señal de autenticación del usuario a la ranura onUserAuthenticated
    connect(m_socket, &MyWebSocket::userAuthenticated, this, &Game::onUserAuthenticated);
    connect(m_socket, &MyWebSocket::gameStarted, this, &Game::onGameStarted);

    // Asignar el layout principal a este widget
    setLayout(m_mainLayout);
}

void Game::onUserAuthenticated()
{
    // Remover NavBarU del layout
    m_mainLayout->removeWidget(m_navBarU);
    m_navBarU->hide();

    // Añadir NavBar al layout
    m_mainLayout->addWidget(m_navBar);
    m_navBar->show();
}

void Game::onGameStarted(const QString& player1, const QString& player2, int tableNumber)
{
    // Crear y configurar la ventana del juego
    GameWindow* gameWindow = new GameWindow(player1, player2, tableNumber, m_socket);

    // Remover el widget actual del layout principal
    if (m_mainLayout->count() > 0) {
        QWidget* currentWidget = m_mainLayout->itemAt(0)->widget();
        m_mainLayout->removeWidget(currentWidget);
        currentWidget->hide();
    }

    // Añadir GameWindow al layout principal
    m_mainLayout->addWidget(gameWindow);
}
