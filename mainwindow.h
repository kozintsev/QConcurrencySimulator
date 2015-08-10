#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool OpenFile();

private:
    Ui::MainWindow *ui;
    QString fileName_DATA, fileName;

//public slots:
//    void slot(const QString& str);
};

#endif // MAINWINDOW_H
