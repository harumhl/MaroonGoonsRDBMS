#ifndef CREATETEAM_H
#define CREATETEAM_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class CreateTeam;
}

class CreateTeam : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTeam(QWidget *parent = 0);
    ~CreateTeam();

private:
    Ui::CreateTeam *ui;
};

#endif // CREATETEAM_H
