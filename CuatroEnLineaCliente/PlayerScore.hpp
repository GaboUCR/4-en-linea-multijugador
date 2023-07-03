#ifndef PLAYERSCORE_H
#define PLAYERSCORE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

/**
 * @class PlayerScore
 * @brief Clase que representa el widget de puntuación de un jugador.
 *
 * Esta clase es responsable de mostrar la puntuación de un jugador, incluyendo su nombre,
 * el número de partidas ganadas y el número de partidas perdidas.
 */
class PlayerScore : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase PlayerScore.
     * @param playerName Nombre del jugador.
     * @param wins Número de partidas ganadas.
     * @param losses Número de partidas perdidas.
     * @param parent Puntero al widget padre. Es nulo por defecto.
     */
    explicit PlayerScore(const QString& playerName, int wins, int losses, QWidget *parent = nullptr);

private:
    QLabel *playerNameLabel; /**< Etiqueta para mostrar el nombre del jugador. */
    QLabel *winsLabel;       /**< Etiqueta para mostrar el número de partidas ganadas. */
    QLabel *lossesLabel;     /**< Etiqueta para mostrar el número de partidas perdidas. */
};

#endif // PLAYERSCORE_H
