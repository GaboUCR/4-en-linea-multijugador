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


QWidget* ShowBoard() {
    QWidget *boardWindow = new QWidget;
    boardWindow->setWindowTitle("Game Board");

    // Crear un layout en grilla
    QGridLayout *gridLayout = new QGridLayout;

    // Establecer el espaciado entre los botones y el margen del layout
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(50, 0, 50, 0);  // Agregar un margen horizontal de 50

    // Crear los botones y añadirlos al layout
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 7; ++col) {
            // Crear un nuevo botón
            QPushButton *button = new QPushButton;

            // Personalizar la apariencia del botón con CSS
            button->setStyleSheet(
                "QPushButton {"
                "  background-color: white;"  // Color de fondo blanco
                "  border: 1px solid black;"  // Bordes negros
                "  border-radius: 25px;"      // Hacer que el botón sea redondo
                "  min-width: 50px;"          // Establecer el ancho mínimo
                "  max-width: 50px;"          // Establecer el ancho máximo
                "  min-height: 50px;"         // Establecer la altura mínima
                "  max-height: 50px;"         // Establecer la altura máxima
                "}"
                "QPushButton:pressed {"
                "  background-color: yellow;"  // Cambiar a amarillo cuando se presiona
                "}"
                );

            // Añadir el botón al layout en la posición correspondiente
            gridLayout->addWidget(button, row, col);
        }
    }

    // Asignar el layout a la ventana
    boardWindow->setLayout(gridLayout);

    return boardWindow;
}

QWidget* ShowPlayers(const QString& player1, const QString& player2, int tableNumber) {
    QWidget *playersWindow = new QWidget;
    playersWindow->setWindowTitle("Players Window");

    QHBoxLayout *layoutMain = new QHBoxLayout;

    QLabel *tableLabel = new QLabel("Table: " + QString::number(tableNumber));

    QLabel *player1Label = new QLabel(player1);
    QLabel *player2Label = new QLabel(player2);

    QLabel *player1PixmapLabel = new QLabel;
    QLabel *player2PixmapLabel = new QLabel;

    QPixmap uncheckedPixmap(":/imagenes/unchecked.png");
    QPixmap checkedPixmap(":/imagenes/checked.png");

    player1PixmapLabel->setPixmap(checkedPixmap);
    player2PixmapLabel->setPixmap(uncheckedPixmap);

    QHBoxLayout *player1Layout = new QHBoxLayout;
    player1Layout->addWidget(player1PixmapLabel);
    player1Layout->addWidget(player1Label);

    QHBoxLayout *player2Layout = new QHBoxLayout;
    player2Layout->addWidget(player2PixmapLabel);
    player2Layout->addWidget(player2Label);

    layoutMain->addWidget(tableLabel);
    layoutMain->addLayout(player1Layout);
    layoutMain->addLayout(player2Layout);

    playersWindow->setLayout(layoutMain);

    return playersWindow;
}


QWidget* ShowNavBarU() {
    QWidget *window = new QWidget;
    window->setWindowTitle("NavBarU");

    QHBoxLayout *layoutNavBar = new QHBoxLayout;

    QPushButton *loginButton = new QPushButton("Log In");
    QPushButton *signinButton = new QPushButton("Sign In");

    layoutNavBar->addWidget(loginButton);
    layoutNavBar->addWidget(signinButton);

    // Crear los widgets de Login y Registro
    QWidget *loginWidget = new QWidget;
    QWidget *registerWidget = new QWidget;

    // Creación de los campos de entrada para el formulario de Login
    QLineEdit* usernameLoginLineEdit = new QLineEdit;
    QLineEdit* passwordLoginLineEdit = new QLineEdit;

    // Creación del layout y añadimos las filas con etiquetas y los campos de entrada
    QFormLayout *loginLayout = new QFormLayout;
    loginLayout->addRow(new QLabel("Username:"), usernameLoginLineEdit);
    loginLayout->addRow(new QLabel("Password:"), passwordLoginLineEdit);

    // Creación del botón de envío para el formulario de Login
    QPushButton *loginSubmitButton = new QPushButton("Submit");
    loginLayout->addWidget(loginSubmitButton);
    loginWidget->setLayout(loginLayout);

    // Conexión del botón a una función que imprime los datos de los campos de entrada
    QObject::connect(loginSubmitButton, &QPushButton::clicked, [usernameLoginLineEdit, passwordLoginLineEdit](){
        QString username = usernameLoginLineEdit->text();
        QString password = passwordLoginLineEdit->text();
        qDebug() << "Login - Username: " << username;
        qDebug() << "Login - Password: " << password;
    });

    // Creación de los campos de entrada para el formulario de Registro
    QLineEdit* usernameRegisterLineEdit = new QLineEdit;
    QLineEdit* passwordRegisterLineEdit = new QLineEdit;
    QLineEdit* confirmPasswordRegisterLineEdit = new QLineEdit;

    // Creación del layout y añadimos las filas con etiquetas y los campos de entrada
    QFormLayout *registerLayout = new QFormLayout;
    registerLayout->addRow(new QLabel("Username:"), usernameRegisterLineEdit);
    registerLayout->addRow(new QLabel("Password:"), passwordRegisterLineEdit);
    registerLayout->addRow(new QLabel("Confirm Password:"), confirmPasswordRegisterLineEdit);

    // Creación del botón de envío para el formulario de Registro
    QPushButton *registerSubmitButton = new QPushButton("Submit");
    registerLayout->addWidget(registerSubmitButton);
    registerWidget->setLayout(registerLayout);

    // Conexión del botón a una función que imprime los datos de los campos de entrada
    QObject::connect(registerSubmitButton, &QPushButton::clicked, [usernameRegisterLineEdit, passwordRegisterLineEdit, confirmPasswordRegisterLineEdit](){
        QString username = usernameRegisterLineEdit->text();
        QString password = passwordRegisterLineEdit->text();
        QString confirmPassword = confirmPasswordRegisterLineEdit->text();
        qDebug() << "Register - Username: " << username;
        qDebug() << "Register - Password: " << password;
        qDebug() << "Register - Confirm Password: " << confirmPassword;
    });

    // Crear el QStackedWidget y agregar los widgets de Login y Registro
    QStackedWidget *stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(registerWidget);

    // Conectar las señales de los botones para cambiar el widget mostrado
    QObject::connect(loginButton, &QPushButton::clicked, [stackedWidget](){ stackedWidget->setCurrentIndex(0); });
    QObject::connect(signinButton, &QPushButton::clicked, [stackedWidget](){ stackedWidget->setCurrentIndex(1); });

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutNavBar);
    layoutMain->addWidget(stackedWidget);

    window->setLayout(layoutMain);

    return window;
}

QWidget* ShowAccount() {
    QWidget *accountWindow = new QWidget;
    accountWindow->setWindowTitle("Account");

    QVBoxLayout *layoutAccount = new QVBoxLayout;

    QLabel *usernameLabel = new QLabel("Gabo");
    QLabel *winsLabel = new QLabel("15 partidas ganadas");

    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    usernameLabel->setFont(font);
    winsLabel->setFont(font);

    layoutAccount->addWidget(usernameLabel);
    layoutAccount->addWidget(winsLabel);

    accountWindow->setLayout(layoutAccount);

    return accountWindow;
}

QWidget* ShowNavBar() {
    QWidget *window = new QWidget;
    window->setWindowTitle("NavBar");

    QHBoxLayout *layoutNavBar = new QHBoxLayout;

    QPushButton *gameLogoButton = new QPushButton("Game Logo");
    QPushButton *previousGamesButton = new QPushButton("Previous Games");
    QPushButton *userButton = new QPushButton("User");

    layoutNavBar->addWidget(gameLogoButton);
    layoutNavBar->addWidget(previousGamesButton);
    layoutNavBar->addWidget(userButton);

    // Crear el widget de la Cuenta
    QWidget *accountWidget = ShowAccount();

    // Crear otros widgets que se necesiten
    QWidget *otherWidget = new QWidget; // Widget de marcador de posición

    // Crear el QStackedWidget y agregar los widgets
    QStackedWidget *stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(otherWidget);
    stackedWidget->addWidget(accountWidget);

    // Conectar las señales de los botones para cambiar el widget mostrado
    QObject::connect(userButton, &QPushButton::clicked, [stackedWidget](){ stackedWidget->setCurrentIndex(1); });
    // Conectar otros botones según sea necesario...

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutNavBar);
    layoutMain->addWidget(stackedWidget);

    window->setLayout(layoutMain);

    return window;
}

QWidget* ShowGameWindow(const QString& player1, const QString& player2, int tableNumber) {
    QWidget *gameWindow = new QWidget;
    gameWindow->setWindowTitle("Game Window");

    QVBoxLayout *layoutMain = new QVBoxLayout;

    QWidget* playersWidget = ShowPlayers(player1, player2, tableNumber);
    QWidget* boardWidget = ShowBoard();

    layoutMain->addWidget(playersWidget);
    layoutMain->addWidget(boardWidget);

    // Establecer las proporciones del espacio que cada widget debe tomar.
    layoutMain->setStretchFactor(playersWidget, 1);
    layoutMain->setStretchFactor(boardWidget, 3);

    gameWindow->setLayout(layoutMain);



    gameWindow->setLayout(layoutMain);

    return gameWindow;
}


int main(int argc, char *argv[]) {

   QApplication app(argc, argv);

//   QWidget* NavBar = ShowPlayers("Gabo", "Gabriel", 4);

    QWidget* e = ShowGameWindow("gabo", "gabo2", 9);

    e->show();

    return app.exec();
}
