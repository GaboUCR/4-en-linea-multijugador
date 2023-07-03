#include "Account.hpp"

Account::Account(MyWebSocket *webSocket, QWidget *parent)
    : QWidget(parent) {

    this->setWindowTitle("Account");

    // Crear el layout vertical para organizar los elementos de la cuenta
    QVBoxLayout *layoutAccount = new QVBoxLayout;

    // Crear etiquetas para el nombre de usuario y las partidas ganadas
    usernameLabel = new QLabel();
    winsLabel = new QLabel();
    lossLabel = new QLabel();
    // Establecer la fuente para las etiquetas
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    usernameLabel->setFont(font);
    winsLabel->setFont(font);
    lossLabel->setFont(font);

    // Agregar las etiquetas al layout
    layoutAccount->addWidget(usernameLabel, 0, Qt::AlignCenter); // Aligned to Center
    layoutAccount->addWidget(winsLabel, 0, Qt::AlignCenter); // Aligned to Center
    layoutAccount->addWidget(lossLabel, 0, Qt::AlignCenter); // Aligned to Center

    // Establecer el layout para este widget
    this->setLayout(layoutAccount);

    // Conectar la señal de MyWebSocket con el slot de Account
    connect(webSocket, &MyWebSocket::accountInfoReceived, this, &Account::updateAccountInfo);
}

void Account::updateAccountInfo(const QString &username, int wins, int loss) {
    // Actualizar las etiquetas con la nueva información
    usernameLabel->setText(username);
    winsLabel->setText(QString::number(wins) + " partidas ganadas");
    lossLabel->setText(QString::number(loss) + " partidas perdidas");
}
