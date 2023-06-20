// Board.cpp
#include "Board.h"

void Board::SetWebSocket(MyWebSocket* socket)
{
    m_socket = socket;
}

void Board::handleButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());  // Determina qué botón emitió la señal
    if (!button) {
        return;
    }

    // Identifica la columna que ha sido pulsada
    int clicked_col = -1;
    for (int col = 0; col < 7; ++col) {
        for (int row = 0; row < 7; ++row) {
            if (buttons[row][col] == button) {
                clicked_col = col;
                break;
            }
        }
        if (clicked_col != -1) {
            break;
        }
    }

    // Busca desde abajo en la columna hasta encontrar el primer espacio vacío
    for (int row = 6; row >= 0; --row) {
        if (boardState[row][clicked_col] == 0) {
            // Aquí encontramos la primera casilla vacía en la columna

            // Construye el mensaje aquí
            QByteArray message;
            QDataStream stream(&message, QIODevice::WriteOnly);
            stream.setVersion(QDataStream::Qt_5_15);
            stream.setByteOrder(QDataStream::LittleEndian);

            stream << (int)0;  // Action
            stream << player_id;
            stream << table;
            stream << row;
            stream << clicked_col;

            m_socket->sendBinaryMessage(message);
            return;


        }
    }

}

Board::Board(int player_id, int table_id, MyWebSocket* socket, QWidget *parent)
    : QWidget(parent), player_id(player_id), table(table_id), m_socket(socket)
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
            connect(button, &QPushButton::clicked, this, &Board::handleButtonClicked);  // Conecta la señal clicked del botón a un nuevo slot

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

            // Inicializa el estado del tablero a 0 (sin piezas)
            boardState[row][col] = 0;
            buttons[row][col] = button;
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
