#ifndef ADDLEAGUETEAMPLAYER_H
#define ADDLEAGUETEAMPLAYER_H

#include <QDialog>

namespace Ui {
class AddLeagueTeamPlayer;
}

class AddLeagueTeamPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit AddLeagueTeamPlayer(QWidget *parent = 0);
    ~AddLeagueTeamPlayer();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddLeagueTeamPlayer *ui;
};

#endif // ADDLEAGUETEAMPLAYER_H
