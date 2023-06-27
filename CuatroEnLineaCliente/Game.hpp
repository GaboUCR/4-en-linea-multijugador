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

private:
    NavBarU *m_navBarU;
    NavBarWidget *m_navBar;
    MyWebSocket *m_socket;
    QVBoxLayout *m_mainLayout; // Layout principal que contendrá NavBarU o NavBar
};
