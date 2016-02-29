#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addleagueteamplayer.h"
#include "uniondiffprodjoin.h"
#include "../Player.h"
#include "displayrelation.h"
#include "openclosewriteexit.h"
#include "selectrelation.h"
#include "projectrelation.h"
#include "displayhelp.h"
#include <vector>
#include <iostream>

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
        MainWindow::instance().setRelation( engine->getRelation(relation_index) );

        DisplayRelation displayRelation;
        displayRelation.setModal(true);
        displayRelation.exec();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->displayBox->clear();

    Engine* engine = MainWindow::instance().getEngine();

    for (int i=0; i< engine->getNumRelations(); i++) {
        QString relationName = QString::fromStdString( engine->getRelation(i)->getName() );
        ui->displayBox->addItem(relationName);
    }
}
