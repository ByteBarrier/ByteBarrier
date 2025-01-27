#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui{
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

    void chooseMode(bool mode);

public slots:
    void treeViewClicked(const QModelIndex &index);

private:
    Ui::SecondWindow *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
};

#endif // SECONDWINDOW_H
