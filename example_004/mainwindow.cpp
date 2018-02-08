#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "c.h" // file with the Python communication

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap plot = callPythonImage(256,128,100);
    ui->label->setPixmap(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
