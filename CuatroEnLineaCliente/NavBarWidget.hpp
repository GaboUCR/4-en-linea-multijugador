#ifndef NAVBARWIDGET_HPP
#define NAVBARWIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include "WS.hpp"

/**
 * @class NavBarWidget
 * @brief Clase que representa un widget de barra de navegación.
 *
 * Esta clase gestiona la barra de navegación, permitiendo cambiar entre
 * diferentes widgets en la barra de navegación.
 */
class NavBarWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase NavBarWidget.
     * @param m_socket Puntero al objeto WebSocket para comunicaciones en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit NavBarWidget(MyWebSocket * m_socket, QWidget *parent = nullptr);

private:
    QHBoxLayout *layoutNavBar;    /**< Layout horizontal para la barra de navegación. */
    QVBoxLayout *layoutMain;      /**< Layout vertical principal que contiene la barra de navegación. */
    QStackedWidget *stackedWidget; /**< Widget apilado que permite cambiar entre diferentes widgets. */
};

#endif // NAVBARWIDGET_HPP
