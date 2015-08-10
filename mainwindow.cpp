#include "filestructure.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "stdafx.h"

#include "CPU.h"
#include "Programm.h"
#include "Computer.h"

#include <iostream>

FileStructure * fs;
QStringList firstLine;
QStringList myConsoleData;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try
    {
    fs = new FileStructure;
    if (OpenFile())
    {
        size_t nPrograms = fs->nPrograms;
        for (int i = 0;  i < fs->fileRead.count(); i++)
        {
            //QString s = QString::number(nPrograms);
            //QMessageBox::information(this, tr("Concurrency Simulator"),
            //                           fs->fileRead[i],
            //                           QMessageBox::Ok, QMessageBox::Ok);
        }
        Computer computer;
        //QObject::connect(computer, SIGNAL(sendSignal(const QString& str)),
        //    this, SLOT(slot(const QString& str));
        //computer.readInputStream(*fs);
        //bool res = computer.loadProgramms(nPrograms);
        //if (res) {
        //     computer.calculate();
        //}
    }
    }
    catch(...)
    {
        QMessageBox::critical(this, tr("Concurrency Simulator"),
                                       tr("Exception"),
                                       QMessageBox::Ok, QMessageBox::Ok);
    }
}

//void MainWindow::slot(const QString& str)
//{
//     ui->mylistWidget->addItem(str);
//}

MainWindow::~MainWindow()
{
    delete ui;
    delete fs;
}

bool MainWindow::OpenFile()
{
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text File"), "/test0.txt", tr("Image Files (*.txt)"));
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        int i = 0;
        while (!stream.atEnd())
        {
            str = stream.readLine();
            ui->mylistWidget->addItem(str);
            if ( i == 0)
            {
                firstLine = str.split(" ");
                fs->nPrograms = firstLine[0].toInt();
            }
            else
            {
            }
            i++;
            fs->fileRead << str;
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
