#include "NavBarWidget.hpp"
#include "Account.hpp"
#include "WS.hpp"

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
    Account *accountWidget = new Account (m_socket); // Suponiendo que ShowAccount está implementado en algún lugar

    // Crear otros widgets que se necesiten
    QWidget *otherWidget = new QWidget; // Widget de marcador de posición

    // Crear el QStackedWidget y agregar los widgets
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(otherWidget);
    stackedWidget->addWidget(accountWidget);

    // Conectar las señales de los botones para cambiar el widget mostrado
    QObject::connect(userButton, &QPushButton::clicked, [this](){ stackedWidget->setCurrentIndex(1); });
    // Conectar otros botones según sea necesario...

    // Crear el layout principal y agregar los layouts de la barra de navegación y el QStackedWidget
    layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutNavBar);
    layoutMain->addWidget(stackedWidget);

    // Establecer el layout principal para este widget
    setLayout(layoutMain);
}


