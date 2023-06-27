#include "NavBarU.hpp"

NavBarU::NavBarU(MyWebSocket* m_socket, QWidget *parent)
    : QWidget(parent), m_socket(m_socket),
    usernameLoginLineEdit(new QLineEdit),
    passwordLoginLineEdit(new QLineEdit),
    usernameRegisterLineEdit(new QLineEdit),
    passwordRegisterLineEdit(new QLineEdit),
    confirmPasswordRegisterLineEdit(new QLineEdit),
    loginMessageLabel(new QLabel),
    registerMessageLabel(new QLabel)
{
    setWindowTitle("NavBarU");

    QHBoxLayout *layoutNavBar = new QHBoxLayout;
    QPushButton *loginButton = new QPushButton("Log In");
    QPushButton *signinButton = new QPushButton("Sign In");

    layoutNavBar->addWidget(loginButton);
    layoutNavBar->addWidget(signinButton);
    connect(m_socket, &MyWebSocket::invalidCredentials, this, &NavBarU::onInvalidCredentials);

    loginMessageLabel->setText("");
    registerMessageLabel->setText("");

    // Formulario de Login
    QFormLayout *loginLayout = new QFormLayout;
    loginLayout->addRow(new QLabel("Username:"), usernameLoginLineEdit);
    loginLayout->addRow(new QLabel("Password:"), passwordLoginLineEdit);
    QPushButton *loginSubmitButton = new QPushButton("Submit");
    loginLayout->addWidget(loginSubmitButton);
    loginLayout->addWidget(loginMessageLabel); // Agrega el mensaje debajo del formulario de login

    QWidget *loginWidget = new QWidget;
    loginWidget->setLayout(loginLayout);

    // Formulario de Registro
    QFormLayout *registerLayout = new QFormLayout;
    registerLayout->addRow(new QLabel("Username:"), usernameRegisterLineEdit);
    registerLayout->addRow(new QLabel("Password:"), passwordRegisterLineEdit);
    registerLayout->addRow(new QLabel("Confirm Password:"), confirmPasswordRegisterLineEdit);
    QPushButton *registerSubmitButton = new QPushButton("Submit");
    registerLayout->addWidget(registerSubmitButton);
    registerLayout->addWidget(registerMessageLabel); // Agrega el mensaje debajo del formulario de registro

    QWidget *registerWidget = new QWidget;
    registerWidget->setLayout(registerLayout);

    // Restricciones de longitud
    usernameLoginLineEdit->setMaxLength(15);
    passwordLoginLineEdit->setMaxLength(20);
    usernameRegisterLineEdit->setMaxLength(15);
    passwordRegisterLineEdit->setMaxLength(20);
    confirmPasswordRegisterLineEdit->setMaxLength(20);

    // StackedWidget
    QStackedWidget *stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(registerWidget);

    // Conexiones
    connect(loginButton, &QPushButton::clicked, [stackedWidget](){ stackedWidget->setCurrentIndex(0); });
    connect(signinButton, &QPushButton::clicked, [stackedWidget](){ stackedWidget->setCurrentIndex(1); });
    connect(loginSubmitButton, &QPushButton::clicked, this, &NavBarU::onLoginSubmit);
    connect(registerSubmitButton, &QPushButton::clicked, this, &NavBarU::onRegisterSubmit);

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutNavBar);
    layoutMain->addWidget(stackedWidget);

    setLayout(layoutMain);
}



void NavBarU::onLoginSubmit()
{
    QString username = usernameLoginLineEdit->text();
    QString password = passwordLoginLineEdit->text();

    QByteArray message;
    message.resize(4 + 15 + 20);
    int sus = login;

    QByteArray usernameBytes = username.toLocal8Bit();
    usernameBytes.append(15 - usernameBytes.size(), ' ');

    QByteArray passwordBytes = password.toLocal8Bit();
    passwordBytes.append(20 - passwordBytes.size(), ' ');

    std::memcpy(message.data(), &sus, 4);
    std::memcpy(message.data() + 4, usernameBytes.data(), 15);
    std::memcpy(message.data() + 19, passwordBytes.data(), 20);

    m_socket->sendBinaryMessage(message);
}

void NavBarU::onInvalidCredentials() {
    registerMessageLabel->setText("Credenciales incorrectas, intente de nuevo.");
    loginMessageLabel->setText("Credenciales incorrectas, intente de nuevo.");
}

void NavBarU::onRegisterSubmit()
{
    QString username = usernameRegisterLineEdit->text();
    QString password = passwordRegisterLineEdit->text();
    QString confirmPassword = confirmPasswordRegisterLineEdit->text();

    if (password == confirmPassword) {
        QByteArray message;
        message.resize(4 + 15 + 20);
        int reg = signin;

        QByteArray usernameBytes = username.toLocal8Bit();
        usernameBytes.append(15 - usernameBytes.size(), ' ');

        QByteArray passwordBytes = password.toLocal8Bit();
        passwordBytes.append(20 - passwordBytes.size(), ' ');

        std::memcpy(message.data(), &reg, 4);
        std::memcpy(message.data() + 4, usernameBytes.data(), 15);
        std::memcpy(message.data() + 19, passwordBytes.data(), 20);

        m_socket->sendBinaryMessage(message);
    } else {
        qDebug() << "Passwords do not match.";
    }
}
