#ifndef SCORES_H
#define SCORES_H

#include <QWidget>
#include <QGridLayout>
#include "WS.hpp"

class Scores : public QWidget
{
    Q_OBJECT

public:
    explicit Scores(MyWebSocket* m_socket, QWidget *parent = nullptr);
    void addPlayerScore(const QString &playerName, int wins, int losses);

public slots:
    void updatePlayerScores(const QList<QVariantMap>& playersInfo);

private:
    QGridLayout *gridLayout;
    MyWebSocket* m_socket;

};

#endif // SCORES_H
