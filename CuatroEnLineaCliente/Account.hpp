#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QString>
#include "WS.hpp"

/**
 * @class Account
 * @brief La clase Account proporciona un widget para mostrar la información de la cuenta del usuario.
 *
 * Este widget muestra el nombre de usuario junto con el número de victorias y derrotas.
 */
class Account : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construye un widget de Account.
     * @param webSocket Puntero a la instancia de MyWebSocket para comunicación.
     * @param parent Widget padre opcional.
     */
    explicit Account(MyWebSocket *webSocket, QWidget *parent = nullptr);

public slots:
    /**
     * @brief Slot para actualizar la información de la cuenta mostrada en el widget.
     * @param username El nombre de usuario que se mostrará.
     * @param wins El número de victorias que se mostrará.
     * @param loss El número de derrotas que se mostrará.
     */
    void updateAccountInfo(const QString &username, int wins, int loss);

private:
    QLabel *usernameLabel; /**< Etiqueta para mostrar el nombre de usuario. */
    QLabel *winsLabel;     /**< Etiqueta para mostrar el número de victorias. */
    QLabel *lossLabel;     /**< Etiqueta para mostrar el número de derrotas. */
};

#endif // ACCOUNT_H

