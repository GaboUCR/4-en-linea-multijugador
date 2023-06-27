#include "NavBarWidget.hpp"
#include "Account.hpp"
#include "WS.hpp"
#include "GameLobbyWindow.hpp"

NavBarWidget::NavBarWidget(MyWebSocket* m_socket, QWidget *parent) : QWidget(parent)
{
    setWindowTitle("NavBar");

    // Crear el layout para la barra de navegación
    layoutNavBar = new QHBoxLayout;

    // Crear los botones para la barra de navegación
    QPushButton *gameLogoButton = new QPushButton("Game Logo");
    QPushButton *previousGamesButton = new QPushButton("Previous Games");
    QPushButton *userButton = new QPushButton("User");

    // Agregar los botones al layout de la barra de navegación
    layoutNavBar->addWidget(gameLogoButton);
    layoutNavBar->addWidget(previousGamesButton);
    layoutNavBar->addWidget(userButton);

    // Crear el widget de la Cuenta
    Account *accountWidget = new Account(m_socket);

    // Crear el widget GameLobbyWindow
    GameLobbyWindow *gameLobbyWindow = new GameLobbyWindow(m_socket);

    // Crear el QStackedWidget y agregar los widgets
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(gameLobbyWindow); // Índice 0
    stackedWidget->addWidget(accountWidget); // Índice 1

    // Conectar las señales de los botones para cambiar el widget mostrado
    QObject::connect(gameLogoButton, &QPushButton::clicked, [this](){ stackedWidget->setCurrentIndex(0); });
    QObject::connect(userButton, &QPushButton::clicked, [this](){ stackedWidget->setCurrentIndex(1); });

    // Crear el layout principal y agregar los layouts de la barra de navegación y el QStackedWidget
    layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutNavBar);
    layoutMain->addWidget(stackedWidget);

    // Establecer el layout principal para este widget
    setLayout(layoutMain);
}


