#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include "secondwindow.h"

namespace Ui{
class SecondWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ok();
    void openModelFile();

private:
    Ui::SecondWindow *ui;
    SecondWindow * secondWindow;
};

#endif // MAINWINDOW_H
