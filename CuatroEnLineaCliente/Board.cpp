// Board.cpp
#include "Board.h"

Board::Board(QWidget *parent) : QWidget(parent)
{
    // Crear un layout en grilla
    gridLayout = new QGridLayout;

    // Establecer el espaciado entre los botones
    gridLayout->setHorizontalSpacing(0);  // Aquí se establece el espaciado horizontal
    gridLayout->setVerticalSpacing(0);  // Aquí se establece el espaciado vertical
    gridLayout->setContentsMargins(400, 10, 400, 10);  // Agregar un margen horizontal de 50

    // llama a un evento de cambio de tamaño llamar el método resizeEvent
    QSize initialSize = size();
    QResizeEvent initialResizeEvent(initialSize, initialSize);
    resizeEvent(&initialResizeEvent);

    // Crear los botones y añadirlos al layout
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 7; ++col) {
            // Crear un nuevo botón
            QPushButton *button = new QPushButton;

            // Personalizar la apariencia del botón con CSS
            button->setStyleSheet(
                "QPushButton {"
                "  background-color: white;"  // Color de fondo blanco
                "  border: 1px solid black;"  // Bordes negros
                "  border-radius: 35px;"      // Hacer que el botón sea redondo
                "  min-width: 70px;"          // Establecer el ancho mínimo
                "  max-width: 70px;"          // Establecer el ancho máximo
                "  min-height: 70px;"         // Establecer la altura mínima
                "  max-height: 70px;"         // Establecer la altura máxima
                "}"
                );

            buttons[row][col] = new QPushButton;
            // Añadir el botón al layout en la posición correspondiente
            gridLayout->addWidget(button, row, col);
        }
    }

    // Asignar el layout a la ventana
    setLayout(gridLayout);
}

void Board::changeButtonColor(int row, int col, ButtonColor color)
{
    if (row < 0 || row >= 7 || col < 0 || col >= 7) {
        // Índices fuera de rango
        return;
    }

    QPushButton *button = buttons[row][col];
    if (color == RED) {
        button->setStyleSheet("QPushButton { background-color: red; } QPushButton:pressed { background-color: red; }");
    } else if (color == YELLOW) {
        button->setStyleSheet("QPushButton { background-color: yellow; } QPushButton:pressed { background-color: yellow; }");
    }
}

void Board::resizeEvent(QResizeEvent *event)
{   //@todo Ajustar diseño responsive
    QSize size = event->size();
    if (size.width() < 800) {
        gridLayout->setContentsMargins(200, 10, 200, 10);
    } else if (size.width() < 1200) {
        gridLayout->setContentsMargins(300, 10, 300, 10);
    } else {
        gridLayout->setContentsMargins(400, 10, 400, 10);
    }
}
