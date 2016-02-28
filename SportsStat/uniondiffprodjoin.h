#ifndef UNIONDIFFPRODJOIN_H
#define UNIONDIFFPRODJOIN_H

#include <QDialog>
#include "mainwindow.h"
#include "../Engine.h"
namespace Ui {
class UnionDiffProdJoin;
}

class UnionDiffProdJoin : public QDialog
{
    Q_OBJECT

public:
    explicit UnionDiffProdJoin(QWidget *parent = 0);
    ~UnionDiffProdJoin();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UnionDiffProdJoin *ui;
    Engine* engine;
};

#endif // UNIONDIFFPRODJOIN_H
