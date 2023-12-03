#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    secondWindow = new SecondWindow();
    secondWindow->hide();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::openModelFile(){

}
void MainWindow::ok(){
    bool valor = false;
    if(this->ui->comboBox->currentIndex() == 1)
        valor = true;
    secondWindow->chooseMode(valor);
    secondWindow->show();
    this->close();
}
