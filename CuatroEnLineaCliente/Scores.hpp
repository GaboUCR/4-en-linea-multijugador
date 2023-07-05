#ifndef SCORES_H
#define SCORES_H

#include <QWidget>
#include <QGridLayout>
#include "WS.hpp"

/**
 * @class Scores
 * @brief Clase que representa el widget de puntuaciones.
 *
 * Esta clase es responsable de mostrar la puntuación de todos los jugadores.
 */
class Scores : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase Scores.
     * @param m_socket Puntero al objeto websocket para comunicaciones en tiempo real.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit Scores(MyWebSocket* m_socket, QWidget *parent = nullptr);

    /**
     * @brief Añade la puntuación de un jugador al widget.
     * @param playerName Nombre del jugador.
     * @param wins Número de partidas ganadas por el jugador.
     * @param losses Número de partidas perdidas por el jugador.
     */
    void addPlayerScore(const QString &playerName, int wins, int losses);

public slots:
    /**
     * @brief Actualiza las puntuaciones de todos los jugadores.
     * @param playersInfo Lista de mapas con la información de cada jugador.
     */
    void updatePlayerScores(const QList<QVariantMap>& playersInfo);

    /**
     * @brief Maneja el evento de clic en el botón.
     */
    void onButtonClicked();

private:
    QGridLayout *gridLayout; /**< Layout en cuadrícula que contiene los elementos del widget. */
    MyWebSocket* m_socket;   /**< Puntero al objeto WebSocket para comunicación en tiempo real. */
};

#endif // SCORES_H
