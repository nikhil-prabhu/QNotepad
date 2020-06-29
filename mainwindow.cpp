#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#define APPLICATION_NAME "QNotepad"             // Application name
#define APPLICATION_VERSION "v0.0.1-alpha"      // Application version

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APPLICATION_NAME);
}

/* MENU ACTIONS */

// File Menu - Quit action
void MainWindow::on_actionQuit_triggered()
{
    auto userChoice = QMessageBox::question(this, "Quit QNotepad", "Are you sure you want to quit?");

    if ( userChoice == QMessageBox::Yes )
    {
        close();        // Quit the application
    }
}

// Help Menu - About QNotepad action
void MainWindow::on_actionAbout_QNotepad_triggered()
{
    QMessageBox::about(this, "About QNotepad", "A simple and lightweight cross-platform notepad application written in Qt and C++."
                                               "\n\n"
                                               "Author: Nikhil Prabhu"
                                               "\n\n"
                                               "License: GNU General Public License v2"
                                               "\n\n"
                                               "Version: " APPLICATION_VERSION);
}

MainWindow::~MainWindow()
{
    delete ui;
}

