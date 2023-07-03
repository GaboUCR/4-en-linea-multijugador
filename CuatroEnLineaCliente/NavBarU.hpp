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

/**
 * @class NavBarU
 * @brief Clase que representa la barra de navegación superior en la interfaz de usuario.
 *
 * Esta clase se encarga de gestionar los componentes de la barra de navegación
 * superior, como los campos de entrada y botones para iniciar sesión y registrarse.
 */
class NavBarU : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase NavBarU.
     * @param m_socket Puntero al objeto WebSocket para comunicaciones en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit NavBarU(MyWebSocket* m_socket, QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot que se activa cuando el usuario envía el formulario de inicio de sesión.
     */
    void onLoginSubmit();

    /**
     * @brief Slot que se activa cuando el usuario envía el formulario de registro.
     */
    void onRegisterSubmit();

    /**
     * @brief Slot que se activa cuando se introducen credenciales no válidas.
     */
    void onInvalidCredentials();

private:
    QLineEdit* usernameLoginLineEdit;            /**< Campo de entrada para el nombre de usuario en inicio de sesión. */
    QLineEdit* passwordLoginLineEdit;            /**< Campo de entrada para la contraseña en inicio de sesión. */
    QLineEdit* usernameRegisterLineEdit;         /**< Campo de entrada para el nombre de usuario en registro. */
    QLineEdit* passwordRegisterLineEdit;         /**< Campo de entrada para la contraseña en registro. */
    QLineEdit* confirmPasswordRegisterLineEdit;  /**< Campo de entrada para confirmar la contraseña en registro. */
    QLabel* loginMessageLabel;                   /**< Etiqueta para mostrar mensajes de inicio de sesión. */
    QLabel* registerMessageLabel;                /**< Etiqueta para mostrar mensajes de registro. */
    MyWebSocket * m_socket;                      /**< Puntero al objeto WebSocket para comunicación en tiempo real. */
};

#endif
