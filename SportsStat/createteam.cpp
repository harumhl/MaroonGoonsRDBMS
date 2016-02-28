#include "createteam.h"
#include "ui_createteam.h"

#include <vector>
#include <iostream>
#include "../Player.h"
#include "mainwindow.h"
using namespace std;

CreateTeam::CreateTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTeam)
{
    ui->setupUi(this);

    // Displaying players' info
    vector<Player*> players = MainWindow::instance().getPlayerVec();

    ui->tableWidget->insertColumn(0); // just name
    ui->tableWidget->setColumnCount(1); // just name

    ui->tableWidget->setRowCount( players.size() );
    for (int i=0; i< players.size(); i++) {
        Player* p = players.at(i);

        QTableWidgetItem* q = new QTableWidgetItem( QString::fromStdString(p->getName()) );
        ui->tableWidget->setItem(i, 0, q);

        cerr << p->getName() << "_" << q->text().toUtf8().constData() << endl;
    }
}

CreateTeam::~CreateTeam()
{
    delete ui;
}
