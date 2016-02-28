#include "openclosewriteexit.h"
#include "ui_openclosewriteexit.h"
#include <string>
#include "mainwindow.h"
#include "../Engine.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
using namespace std;

OpenCloseWriteExit::OpenCloseWriteExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenCloseWriteExit)
{
    ui->setupUi(this);

    ui->filenameE->setText("i.e. Mac: /Users/username/... Windows: C://...");
}

OpenCloseWriteExit::~OpenCloseWriteExit()
{
    delete ui;
}

void OpenCloseWriteExit::on_buttonBox_accepted()
{
    if (ui->comboBox->currentText() == "Exit") MainWindow::instance().getEngine()->exit_();

    QString filenameQ = ui->filenameE->text();

    Engine* engine = MainWindow::instance().getEngine();

    if (ui->comboBox->currentText() == "Open") {
        // Getting the file name correctly
        string fileName = filenameQ.toUtf8().constData();

        /* Mac builds and runs the program in a different directory, thus it's hard to get it
        QString currentpathQ = QDir::currentPath();
        ///// This setup aka directory movement is only for Mac setting
        QDir qd(currentpathQ); qd.cdUp(); qd.cd("SportsStat");
        string currentPath = qd.absolutePath().toUtf8().constData();
        string filePathName = currentPath+"/"+fileName;
        */

        // Testing
        QFile file( QString::fromStdString(fileName) );
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "info", file.errorString());
        }

        engine->open(fileName);
    }
    else if (ui->comboBox->currentText() == "Close") {
        engine->close( filenameQ.toUtf8().constData() );
    }
    else if (ui->comboBox->currentText() == "Write") {
        engine->write( filenameQ.toUtf8().constData() );
    }
}
