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

            stream << (int)board;  // Action
            stream << m_socket->getSessionId();
            stream << table;
            stream << row;
            stream << clicked_col;

            m_socket->sendBinaryMessage(message);
            return;
        }
    }

}

Board::Board(int table_id, MyWebSocket* socket, QWidget *parent)
    : QWidget(parent), table(table_id), m_socket(socket)
{

    connect(socket, &MyWebSocket::boardColorChanged, this, &Board::changeButtonColor, Qt::DirectConnection);

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
            boardColor[row][col] = -1;
            buttons[row][col] = button;
            // Añadir el botón al layout en la posición correspondiente
            gridLayout->addWidget(button, row, col);
        }
    }

    // Asignar el layout a la ventana
    setLayout(gridLayout);
}

Board::~Board()
{
    // Liberar la memoria de los botones
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 7; ++col) {
            delete buttons[row][col];
        }
    }

    // Liberar la memoria del layout
    delete gridLayout;
}

void Board::changeButtonColor(int row, int col, int color, int id)
{
    if (row < 0 || row >= 7 || col < 0 || col >= 7) {
        // Índices fuera de rango
        return;
    }

    QPushButton *button = buttons[row][col];
    boardState[row][col] = 1;
    boardColor[row][col] = color;

    QString baseStyle =
        "QPushButton {"
        "  background-color: %1;"
        "  border: 1px solid black;"
        "  border-radius: 35px;"
        "  min-width: 70px;"
        "  max-width: 70px;"
        "  min-height: 70px;"
        "  max-height: 70px;"
        "} "
        "QPushButton:pressed {"
        "  background-color: %1;"
        "}";

    if (color == RED) {
        button->setStyleSheet(baseStyle.arg("red"));
    } else if (color == YELLOW) {
        button->setStyleSheet(baseStyle.arg("yellow"));
    }
//    qDebug() << "HasWon: " << hasWon(color, row, col);
//    qDebug() << "ID: " << id;
//    qDebug() << "Session ID: " << m_socket->getSessionId();


    // Ahora primero cambiamos el color y luego verificamos si el jugador ha ganado
    if (hasWon(color, row, col) && id == m_socket->getSessionId()) {
        // Construir el mensaje para indicar que el jugador ha ganado
        QByteArray message;
        QDataStream stream(&message, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_15);
        stream.setByteOrder(QDataStream::LittleEndian);

        // Añadir la acción GameWon, el color del jugador, el número de la mesa y el ID de la sesión
        stream << (int)gameWon;
        stream << color;
        stream << table;
        stream << m_socket->getSessionId();

        qDebug() << "Mensaje enviado (hex):" << message.toHex();

        // Enviar el mensaje
        m_socket->sendBinaryMessage(message);
    }
}


bool Board::hasWon(int color, int lastMoveRow, int lastMoveCol)
{
    // Direcciones: horizontal, vertical, diagonal principal, diagonal secundaria
    const int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    // Iterar por cada dirección
    for (int dir = 0; dir < 4; ++dir) {
        int dx = directions[dir][0];
        int dy = directions[dir][1];

        // Contar cuántas fichas consecutivas del mismo color hay en esta dirección
        int count = 1;  // La ficha recién colocada
        for (int step = 1; step < 4; ++step) {
            int x = lastMoveCol + step * dx;
            int y = lastMoveRow + step * dy;
            if (x < 0 || x >= 7 || y < 0 || y >= 7 || boardColor[y][x] != color) {
                break;  // Fuera de los límites o no coincide con el color
            }
            count++;
        }

        // Contar en la dirección opuesta
        for (int step = 1; step < 4; ++step) {
            int x = lastMoveCol - step * dx;
            int y = lastMoveRow - step * dy;
            if (x < 0 || x >= 7 || y < 0 || y >= 7 || boardColor[y][x] != color) {
                break;  // Fuera de los límites o no coincide con el color
            }
            count++;
        }

        // Si hay al menos 4 fichas consecutivas, el jugador ha ganado
        if (count >= 4) {
            return true;
        }
    }

    // Si llegamos aquí, no hay 4 fichas consecutivas en ninguna dirección
    return false;
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
