#ifndef CREATEPLAYER_H
#define CREATEPLAYER_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class CreatePlayer;
}

class CreatePlayer : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePlayer(QWidget *parent = 0);
    ~CreatePlayer();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CreatePlayer *ui;
};

#endif // CREATEPLAYER_H
