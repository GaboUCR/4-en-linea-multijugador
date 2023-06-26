// MesaWindow.cpp
#include "MesaWindow.hpp"
#include <QCheckBox>

MesaWindow::MesaWindow(int mesaNumber, QWidget *parent) : QWidget(parent)
{
    // Setup layout
    layout = new QVBoxLayout(this);

    // Setup label with mesa number
    mesaLabel = new QLabel(QString("Mesa %1").arg(mesaNumber), this);
    layout->addWidget(mesaLabel);

    // Setup player buttons
    player1Button = new QPushButton(this);
    player2Button = new QPushButton(this);

    // Connect buttons to slots
    connect(player1Button, &QPushButton::clicked, this, &MesaWindow::onButtonClicked);
    connect(player2Button, &QPushButton::clicked, this, &MesaWindow::onButtonClicked);

    // Add buttons to layout
    layout->addWidget(player1Button);
    layout->addWidget(player2Button);
}

void MesaWindow::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        button->setText("Player Name"); // you can set player name dynamically
        button->setIcon(QIcon(":/path/to/checked-checkbox.png")); // set the checked checkbox icon
    }
}
