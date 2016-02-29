#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addleagueteamplayer.h"
#include "uniondiffprodjoin.h"
#include "../Engine.h"
#include "../Player.h"
#include "displayrelation.h"
#include "openclosewriteexit.h"
#include "selectrelation.h"
#include "projectrelation.h"
#include "displayhelp.h"
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newPlayer(Player* cp) {
    playerVec.push_back(cp);
}

void MainWindow::on_ExecuteButton_clicked()
{
    if (ui->commandBox->currentText() == "Display Help") {
        DisplayHelp displayHelp;
        displayHelp.setModal(true);
        displayHelp.exec();
    }
    else if (ui->commandBox->currentText() == "Enter a new league, team, or player") {
        AddLeagueTeamPlayer addLeagueTeamPlayer;
        addLeagueTeamPlayer.setModal(true);
        addLeagueTeamPlayer.exec();
    }
    else if (ui->commandBox->currentText() == "Select a relation/table") {
        SelectRelation selectRelation;
        selectRelation.setModal(true);
        selectRelation.exec();
    }
    else if (ui->commandBox->currentText() == "Project a relation/table") {
        ProjectRelation projectRelation;
        projectRelation.setModal(true);
        projectRelation.exec();
    }
    else if (ui->commandBox->currentText() == "Union, Difference, Cross Product, Natural Join") {
        UnionDiffProdJoin unionDiffProdJoin;
        unionDiffProdJoin.setModal(true);
        unionDiffProdJoin.exec();
    }
    else if (ui->commandBox->currentText() == "Open, Close, Write, Exit") {
        OpenCloseWriteExit openRelation;
        openRelation.setModal(true);
        openRelation.exec();
    }
    else if (ui->commandBox->currentText() == "Display a relation/table") {
        // Setting the chosen relation
        Engine* engine = MainWindow::instance().getEngine();

        string relation = ui->displayBox->currentText().toUtf8().constData();
        int relation_index = engine->findRelation(relation);
        if (relation_index == -1) {
            QString errorMessage = QString::fromStdString("Relation not found");
            QMessageBox::information(0, "info", errorMessage);
        }
        else {
            MainWindow::instance().setRelation( engine->getRelation(relation_index) );

            DisplayRelation displayRelation;
            displayRelation.setModal(true);
            displayRelation.exec();
        }
    }
}

void OpenCloseWriteExit::on_loadAllButton_clicked()
{
    string fileName1 = "../MLSdataTables/1.txt";
    string fileName2 = "../MLSdataTables/2.txt";
    string fileName3 = "../MLSdataTables/3.txt";
    string fileName4 = "../MLSdataTables/4.txt";
    string fileName5 = "../MLSdataTables/5.txt";
    string fileName6 = "../MLSdataTables/6.txt";
    string fileName7 = "../MLSdataTables/7.txt";
    string fileName8 = "../MLSdataTables/8.txt";
    string fileName9 = "../MLSdataTables/9.txt";
    string fileName10 = "../MLSdataTables/10.txt";
    string fileName11 = "../MLSdataTables/11.txt";
    string fileName12 = "../MLSdataTables/12.txt";
    string fileName13 = "../MLSdataTables/13.txt";
    string fileName14 = "../MLSdataTables/14.txt";
    string fileName15 = "../MLSdataTables/15.txt";
    string fileName16 = "../MLSdataTables/16.txt";
    string fileName17 = "../MLSdataTables/17.txt";
    string fileName18 = "../MLSdataTables/18.txt";
    string s1 = "../PLdataTables/1.txt";
    string s2 = "../PLdataTables/2.txt";
    string s3 = "../PLdataTables/3.txt";
    string s4 = "../PLdataTables/4.txt";
    string s5 = "../PLdataTables/5.txt";
    string s6 = "../PLdataTables/6.txt";
    string s7 = "../PLdataTables/7.txt";
    string s8 = "../PLdataTables/8.txt";
    string s9 = "../PLdataTables/9.txt";
    string s10 = "../PLdataTables/10.txt";
    string s11 = "../PLdataTables/11.txt";
    string s12 = "../PLdataTables/12.txt";
    string s13 = "../PLdataTables/13.txt";
    string s14 = "../PLdataTables/14.txt";



    Engine* engine = MainWindow::instance().getEngine();

    QFile file( QString::fromStdString(fileName1) );
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "info", file.errorString());
    }
    else {
        engine->open(fileName1);
        engine->open(fileName2);
        engine->open(fileName3);
        engine->open(fileName4);
        engine->open(fileName5);
        engine->open(fileName6);
        engine->open(fileName7);
        engine->open(fileName8);
        engine->open(fileName9);
        engine->open(fileName10);
        engine->open(fileName11);
        engine->open(fileName12);
        engine->open(fileName13);
        engine->open(fileName14);
        engine->open(fileName15);
        engine->open(fileName16);
        engine->open(fileName17);
        engine->open(fileName18);
        engine->open(s1);
        engine->open(s2);
        engine->open(s3);
        engine->open(s4);
        engine->open(s5);
        engine->open(s6);
        engine->open(s7);
        engine->open(s8);
        engine->open(s10);
        engine->open(s11);
        engine->open(s12);
        engine->open(s13);
        engine->open(s14);
    }
}
