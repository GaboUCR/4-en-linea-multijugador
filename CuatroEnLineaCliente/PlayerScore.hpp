#ifndef PLAYERSCORE_H
#define PLAYERSCORE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class PlayerScore : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerScore(const QString& playerName, int wins, int losses, QWidget *parent = nullptr);

private:
    QLabel *playerNameLabel;
    QLabel *winsLabel;
    QLabel *lossesLabel;
};

#endif // PLAYERSCORE_H
