#ifndef NAVBARU_H
#define NAVBARU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>
#include <QDebug>
#include "WS.hpp"

class NavBarU : public QWidget
{
    Q_OBJECT

public:
    explicit NavBarU(MyWebSocket* m_socket, QWidget *parent = nullptr);

private slots:
    void onLoginSubmit();
    void onRegisterSubmit();

private:
    QLineEdit* usernameLoginLineEdit;
    QLineEdit* passwordLoginLineEdit;
    QLineEdit* usernameRegisterLineEdit;
    QLineEdit* passwordRegisterLineEdit;
    QLineEdit* confirmPasswordRegisterLineEdit;
    MyWebSocket * m_socket;
};

#endif
