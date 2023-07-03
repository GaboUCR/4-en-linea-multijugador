#include "GameWindow.hpp"
#include "Board.h"
#include "Players.hpp"

GameWindow::GameWindow(const QString& player1, const QString& player2, int tableNumber, MyWebSocket* m_socket, QWidget* parent)
    : QWidget(parent) {

    // Configurar el título de la ventana
    setWindowTitle("Game Window");

    // Crear el layout principal
    QVBoxLayout* layoutMain = new QVBoxLayout;

    // Crear instancias de los widgets de jugadores y tablero
    Players* playersWidget = new Players(player1, player2, tableNumber, m_socket);
    Board* boardWidget = new Board(tableNumber, m_socket);

    // Agregar los widgets al layout
    layoutMain->addWidget(playersWidget);
    layoutMain->addWidget(boardWidget);

    // Establecer las proporciones del espacio que cada widget debe tomar.
    layoutMain->setStretchFactor(playersWidget, 1);
    layoutMain->setStretchFactor(boardWidget, 8);

    // Establecer el layout en este widget
    setLayout(layoutMain);
}
