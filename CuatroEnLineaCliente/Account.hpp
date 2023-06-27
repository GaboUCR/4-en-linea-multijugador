#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QString>
#include "WS.hpp"

class Account : public QWidget {
    Q_OBJECT

public:
    // Constructor que acepta una instancia de MyWebSocket
    explicit Account(MyWebSocket *webSocket, QWidget *parent = nullptr);

public slots:
    // Slot para actualizar la información de la cuenta
    void updateAccountInfo(const QString &username, int wins, int loss);

private:
    // Atributos
    QLabel *usernameLabel;
    QLabel *winsLabel;
    QLabel *lossLabel;
};

#endif // ACCOUNT_H
