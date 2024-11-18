#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onOpenButtonClicked(); //Se ejecuta el Botón Abrir
    void onSaveButtonClicked(); //Se ejecuta el Boton Guardar
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
