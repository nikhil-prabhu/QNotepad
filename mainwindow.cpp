#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#define APPLICATION_NAME "QNotepad"             // Application name
#define APPLICATION_VERSION "v0.0.1-alpha"      // Application version

// Detect operating system
QString getOsName()
{
#if defined(Q_OS_MACOS)
return QLatin1String("macOS");
#elif defined(Q_OS_WIN)
return QLatin1String("Microsoft Windows");
#elif defined(Q_OS_LINUX)
return QLatin1String("GNU/Linux");
#elif defined(Q_OS_UNIX)
return QLatin1String("UNIX");
#else
return QLatin1String("Unknown");
#endif
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window title
    this->setWindowTitle(APPLICATION_NAME " - untitled");

    // Set window icon
    QPixmap applicationIcon(":/img/assets/qnotepad.svg");
    this->setWindowIcon(applicationIcon);
}

/* MENU ACTIONS */

// File Menu - Open action
void MainWindow::on_actionOpen_triggered()
{
    // Prompt user for file to open
    QString filePath = QFileDialog::getOpenFileName(this, "Open file");

    if ( !filePath.isEmpty() )
    {
        QFile file(filePath);   // Create QFile object

        if ( !file.open(QIODevice::ReadOnly) )
        {
            // Error opening file
            QMessageBox::critical(this, "Open file - Error", "Error opening file");
            return;
        }

        // Read file content and display in notepad text area
        QTextStream in(&file);
        ui->notepadTextArea->setPlainText(in.readAll());

        // Add filename to window title
        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());
        this->setWindowTitle(APPLICATION_NAME " - " + fileName);

        // Add success message to statusbar
        ui->statusbar->showMessage("File '" + fileName + "' opened.");

        // Close file
        file.close();
    }
}

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
    QString currentOs = getOsName();    // Get current OS name

    QMessageBox::about(this, "About QNotepad", "A simple and lightweight cross-platform notepad application written in Qt and C++."
                                               "\n\n"
                                               "Author: Nikhil Prabhu."
                                               "\n\n"
                                               "License: GNU General Public License v2."
                                               "\n\n"
                                               "Version: " APPLICATION_VERSION "."
                                               "\n\n"
                                               "OS: " + currentOs + ".");
}

// Help Menu - About Qt action
void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

