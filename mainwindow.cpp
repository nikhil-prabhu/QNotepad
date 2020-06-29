#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#define APPLICATION_NAME "QNotepad"     // Application name

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APPLICATION_NAME);
}

/* MENU ACTIONS */

// Quit action
void MainWindow::on_actionQuit_triggered()
{
    auto userChoice = QMessageBox::question(this, "Quit QNotepad", "Are you sure you want to quit?");

    if ( userChoice == QMessageBox::Yes )
    {
        close();        // Quit the application
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

