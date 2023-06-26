#ifndef NAVBARWIDGET_HPP
#define NAVBARWIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include "WS.hpp"

class NavBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavBarWidget(MyWebSocket * m_socket,QWidget *parent = nullptr);

private:
    QHBoxLayout *layoutNavBar;
    QVBoxLayout *layoutMain;
    QStackedWidget *stackedWidget;
};

#endif // NAVBARWIDGET_HPP
