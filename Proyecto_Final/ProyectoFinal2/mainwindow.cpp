#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->Abrir,&QPushButton::clicked,this,&MainWindow::onOpenButtonClicked);
    connect(ui->Guardar,&QPushButton::clicked,this,&MainWindow::onSaveButtonClicked);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onOpenButtonClicked() {
    //Abre un cuadro de dialogo para seleccionar un archivo de texto
    QString fileName= QFileDialog::getOpenFileName(this,"Abrir Archivo de Texto","","Archivos de Texto (*.txt)");

    //Verificar si se selecciono un archivo (la cadena no esta vacia)
    if(!fileName.isEmpty()) {
        QFile file(fileName); //Crea un objeto QFile con el nombre del archivo seleccionado
        //Intenta abrir el archivo en modo solo lectura y como texto
        if(file.open(QIODevice::ReadOnly  |  QIODevice::Text)){
            QTextStream in(&file); //Crea un flujo de texto para leer el contenido del archivo
            ui->textEdit->setText(in.readAll()); //Lee todo el contenido del archivo y lo muestra en QTtextEdit
            file.close(); //cierra el archivo despues de leerlo
        }  else{
            QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
        }
    }

}

void MainWindow::onSaveButtonClicked() {

    QString fileName= QFileDialog::getSaveFileName(this,"Guardar Archivo de Texto","","Archivos de Texto (*.txt)");

    if(!fileName.isEmpty()){
        QFile file(fileName);
        //Intenta abrir el archivo en modo solo lectura y como texto
        if(file.open(QIODevice::WriteOnly  |  QIODevice::Text)) {
            QTextStream out(&file); //Crea un flujo de texto para escribir el archivo
            out << ui->textEdit->toPlainText(); //Escribe el contenido de QTextEdit en el archivo
            file.close();
        }  else{
            QMessageBox::warning(this,"Error","No se pudo guardar el archivo");
        }

    }
}
