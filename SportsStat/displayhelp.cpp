#include "displayhelp.h"
#include "ui_displayhelp.h"

DisplayHelp::DisplayHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayHelp)
{
    ui->setupUi(this);
}

DisplayHelp::~DisplayHelp()
{
    delete ui;
}
