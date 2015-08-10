#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "stdafx.h"

#include "CPU.h"
#include "Programm.h"
#include "Computer.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (OpenFile())
    {
        size_t nPrograms;
        std::cin >> nPrograms;
        Computer computer;
        computer.readInputStream();
        //bool res = computer.loadProgramms(nPrograms);
        //if (res) {
        //     computer.calculate();
        //}
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::OpenFile()
{
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text File"), "/home", tr("Image Files (*.txt)"));
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            str = stream.readLine();
            std::cout << str.toStdString() << std::endl;
            //qDebug() << str;
        }
        if(stream.status()!= QTextStream::Ok)
        {
            QMessageBox::critical(this, tr("Concurrency Simulator"),
                                           tr("Read file error"),
                                           QMessageBox::Ok, QMessageBox::Ok);
        }
        file.close();
        return true;
    }
    return false;
}
