#include "mainwindow.h"
#include "ui_mainwindow.h"

#define APPLICATION_NAME "QNotepad"     // Application name

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APPLICATION_NAME);
}

MainWindow::~MainWindow()
{
    delete ui;
}

