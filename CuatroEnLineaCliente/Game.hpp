#include <QWidget>
#include "WS.hpp"
#include "NavBarU.hpp"
#include "NavBarWidget.hpp"

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(MyWebSocket* m_socket, QWidget *parent = nullptr);

private slots:
    void onUserAuthenticated();
    void onGameStarted(const QString& player1, const QString& player2, int tableNumber);

private:
    NavBarU *m_navBarU;
    NavBarWidget *m_navBar;
    MyWebSocket *m_socket;
    QVBoxLayout *m_mainLayout; // Layout principal que contendrá NavBarU o
    // En la sección de signals de tu clase Game, agrega:
signals:
    void gameEnded();

    // En la sección de slots de tu clase Game, agrega:
public slots:
    void returnToLobby();

};
