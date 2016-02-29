#include "addleagueteamplayer.h"
#include "ui_addleagueteamplayer.h"
#include "mainwindow.h"
#include <string>
#include <stdlib.h> // atoi
#include "../Player.h"
using namespace std;

AddLeagueTeamPlayer::AddLeagueTeamPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLeagueTeamPlayer)
{
    ui->setupUi(this);

    ui->pAgeE->setValidator( new QIntValidator(0, 150, this) );
}

AddLeagueTeamPlayer::~AddLeagueTeamPlayer()
{
    delete ui;
}

void AddLeagueTeamPlayer::on_buttonBox_accepted()
{
    QString pNameQ = ui->pNameE->text();
    string pName = pNameQ.toUtf8().constData();

    QString pAgeQ = ui->pAgeE->text();
    string pAge = pAgeQ.toUtf8().constData();
    int pAgeI = atoi (pAge.c_str());

    MainWindow::instance().addPlayer( new Player(pName, pAgeI) );
}
