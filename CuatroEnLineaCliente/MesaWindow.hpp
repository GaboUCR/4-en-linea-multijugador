// MesaWindow.hpp
#ifndef MESAWINDOW_HPP
#define MESAWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MesaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MesaWindow(int mesaNumber, QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLabel *mesaLabel;
    QPushButton *player1Button;
    QPushButton *player2Button;
    QVBoxLayout *layout;
};

#endif // MESAWINDOW_HPP
