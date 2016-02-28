#include "createplayer.h"
#include "ui_createplayer.h"

#include <string>
#include <stdlib.h>     /* atoi */
#include <iostream>
using namespace std;

CreatePlayer::CreatePlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePlayer)
{
    ui->setupUi(this);

    ui->pAgeE->setValidator( new QIntValidator(0, 150, this) );
}

CreatePlayer::~CreatePlayer()
{
    delete ui;
}

void CreatePlayer::on_buttonBox_accepted()
{
    // Player name
    QString qsName = ui->pNameE->text();
    string sName = qsName.toUtf8().constData();

    // Player age
    QString qsAge = ui->pAgeE->text();
    int iAge = std::stoi(qsAge.toUtf8().constData()); // it won't fail

    MainWindow::instance().newPlayer(new Player(sName, iAge));
}
