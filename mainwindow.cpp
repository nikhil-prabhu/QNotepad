#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>

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

// Current file name
QString fileName = "untitled";

// Current file path
QString filePath;

// Current file save status
bool fileIsSaved = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window title
    this->setWindowTitle(APPLICATION_NAME " - " + fileName);

    // Set window icon
    QPixmap applicationIcon(":/img/assets/qnotepad.svg");
    this->setWindowIcon(applicationIcon);
}

/* MENU ACTIONS */

// File Menu - Open action
void MainWindow::on_actionOpen_triggered()
{
    // Prompt user for file to open
    filePath = QFileDialog::getOpenFileName(this, "Open file");

    if ( !filePath.isEmpty() )
    {
        QFile file(filePath);   // Create QFile object

        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            // Error opening file
            QMessageBox::critical(this, "Open file - Error", "Error opening file.");
            return;
        }

        // Read file content and display in notepad text area
        QTextStream in(&file);
        ui->notepadTextArea->setPlainText(in.readAll());

        // Add filename to window title
        QFileInfo fileInfo(file.fileName());
        fileName = fileInfo.fileName();
        this->setWindowTitle(APPLICATION_NAME " - " + fileName);

        // Add success message to statusbar
        ui->statusbar->showMessage("File '" + fileName + "' opened.");

        // Change saved status to true
        fileIsSaved = true;

        // Close file
        file.close();
    }
}

// File Menu - Save action
void MainWindow::on_actionSave_triggered()
{
    if ( fileName == "untitled" )
    {
        on_actionSave_as_triggered();
    }
    else
    {
        QFile file(filePath);   // Create QFile object

        if ( !file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
        {
            // Error saving to file
            QMessageBox::critical(this, "Save file - Error", "Error saving to file.");
        }
        else
        {
            QTextStream out(&file);
            QString content = ui->notepadTextArea->toPlainText();

            // Write to file
            out << content;

            // Close file
            file.close();

            // Remove asterisk from next to file name on window title
            this->setWindowTitle(APPLICATION_NAME " - " + fileName);

            // Add success message to statusbar
            ui->statusbar->showMessage("File '" + fileName + "' saved.");

            // Set saved status to true
            fileIsSaved = true;
        }
    }
}

// File Menu - Save as action
void MainWindow::on_actionSave_as_triggered()
{
    filePath = QFileDialog::getSaveFileName(this, "Save as");

    if ( !filePath.isEmpty() )
    {
        QFile file(filePath);   // Create QFile object

        if ( !file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
        {
            // Error saving to file
            QMessageBox::critical(this, "Save file - Error", "Error saving to file.");
        }
        else
        {
            QTextStream out(&file);
            QString content = ui->notepadTextArea->toPlainText();

            // Write to file
            out << content;

            // Close file
            file.close();

            // Set file name to new name of file
            QFileInfo fileInfo(file.fileName());
            fileName = fileInfo.fileName();

            // Change file name in window title
            this->setWindowTitle(APPLICATION_NAME " - " + fileName);

            // Add success message to statusbar
            ui->statusbar->showMessage("File '" + fileName + "' saved.");

            // Set saved status to true
            fileIsSaved = true;
        }
    }
}

// File Menu - Quit action
void MainWindow::on_actionQuit_triggered()
{
    if ( fileIsSaved == false )
    {
        auto userChoice = QMessageBox::question(this, "Quit QNotepad", "You have unsaved changes. Are you sure you want to quit?");

        if ( userChoice == QMessageBox::Yes )
        {
            close();
        }
    }
    else
    {
        close();
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


void MainWindow::on_notepadTextArea_textChanged()
{
    // Change saved status
    fileIsSaved = false;

    // Clear statubar
    ui->statusbar->clearMessage();

    // Add an asterisk next to file name on window title
    this->setWindowTitle(APPLICATION_NAME " - " + fileName + "*");
}
