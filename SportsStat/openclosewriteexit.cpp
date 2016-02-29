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
        else
            engine->open(fileName);
    }
    else if (ui->comboBox->currentText() == "Close") {
        string relation = filenameQ.toUtf8().constData();
        int relation_index = engine->findRelation(relation);

        if (relation_index == -1) {
            QString errorMessage = QString::fromStdString("Relation not found");
            QMessageBox::information(0, "info", errorMessage);
        }
        else
            engine->close(relation);
    }
    else if (ui->comboBox->currentText() == "Write") {
        string relation = filenameQ.toUtf8().constData();
        int relation_index = engine->findRelation(relation);

        if (relation_index == -1) {
            QString errorMessage = QString::fromStdString("Relation not found");
            QMessageBox::information(0, "info", errorMessage);
        }
        else
            engine->write(relation);
    }
}

void OpenCloseWriteExit::on_loadAllButton_clicked()
{
    string fileName1 = "/Users/HaruLee/GitHub/MaroonGoons-P1D4/input.txt";
    string fileName2 = "/Users/HaruLee/GitHub/MaroonGoons-P1D4/input2.txt";

    Engine* engine = MainWindow::instance().getEngine();

    QFile file( QString::fromStdString(fileName1) );
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "info", file.errorString());
    }
    else {
        engine->open(fileName1);
        engine->open(fileName2);
    }
}
