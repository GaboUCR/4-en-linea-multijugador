#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief La clase MainWindow representa la ventana principal de la aplicación.
 *
 * Esta clase hereda de QMainWindow y es la interfaz gráfica principal donde se puede
 * incorporar menús, barras de herramientas, y widgets.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase MainWindow.
     *
     * Crea una nueva ventana principal.
     *
     * @param parent El widget padre. Es opcional y por defecto es nullptr.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase MainWindow.
     *
     * Limpia los recursos utilizados por la ventana principal.
     */
    ~MainWindow();

private:
    /**
     * @brief Puntero a la interfaz de usuario.
     *
     * Este miembro almacena un puntero a la interfaz de usuario generada por el archivo .ui.
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
