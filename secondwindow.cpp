#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QStandardPaths>

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

    // Creates our new model and populate
    QString mPath = "/", fPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    std::string aux = fPath.toStdString();
    printf("fPath = %s\n", aux.c_str());

    dirModel = new QFileSystemModel(this);

    // Set filter
    dirModel->setFilter(QDir::NoDotAndDotDot |
                        QDir::AllDirs);

    // QFileSystemModel requires root path
    dirModel->setRootPath(mPath);

    // Attach the model to the view
    ui->treeView->setModel(dirModel);

    ui->treeView->setRootIndex(dirModel->index(fPath));

    // FILES

    fileModel = new QFileSystemModel(this);

    // Set filter
    fileModel->setFilter(QDir::NoDotAndDotDot |
                         QDir::Files);

    // QFileSystemModel requires root path
    fileModel->setRootPath(mPath);

    // Attach the model to the view
    ui->listView->setModel(fileModel);

    ui->listView->setRootIndex(fileModel->index(fPath));
}

SecondWindow::~SecondWindow(){
    delete ui;
}


void SecondWindow::chooseMode(bool mode){
    if(mode){
        //
    }
    else{

    }
}

void SecondWindow::treeViewClicked(const QModelIndex &index){
        // TreeView clicked
        // 1. We need to extract path
        // 2. Set that path into our ListView

        // Get the full path of the item that's user clicked on
        QString mPath = dirModel->fileInfo(index).absoluteFilePath();
        ui->listView->setRootIndex(fileModel->setRootPath(mPath));
}
