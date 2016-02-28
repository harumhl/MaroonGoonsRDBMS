#include "uniondiffprodjoin.h"
#include "ui_uniondiffprodjoin.h"
#include "../Engine.h"
#include "../Engine.cpp"
#include "../Tree.h"
#include "../Tree.cpp"
#include "../TreeNode.h"
#include "../Condition.h"
#include "createteam.h"
#include "displayrelation.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

UnionDiffProdJoin::UnionDiffProdJoin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnionDiffProdJoin)
{
    ui->setupUi(this);

    Engine* engine = MainWindow::instance().getEngine();

    for (int i=0; i< engine->getNumRelations(); i++) {
        QString relationName = QString::fromStdString( engine->getRelation(i)->getName() );
        ui->option1Box->addItem(relationName);
        ui->option2Box->addItem(relationName);
    }
}

UnionDiffProdJoin::~UnionDiffProdJoin()
{
    delete ui;
}

void UnionDiffProdJoin::on_buttonBox_accepted()
{
    string relation1 = ui->option1Box->currentText().toUtf8().constData();
    string relation2 = ui->option2Box->currentText().toUtf8().constData();

    Engine* engine = MainWindow::instance().getEngine();

    // Relational Algebra computation
    if (ui->selectionBox->currentText() == "Union") {
        MainWindow::instance().setRelation( engine->union_(relation1, relation2) );
    }
    else if (ui->selectionBox->currentText() == "Difference") {
        MainWindow::instance().setRelation( engine->difference(relation1, relation2) );
    }
    else if (ui->selectionBox->currentText() == "Cross Product") {
        MainWindow::instance().setRelation( engine->crossProduct(relation1, relation2) );
    }
    else if (ui->selectionBox->currentText() == "Natural Join") {
        MainWindow::instance().setRelation( engine->naturalJoin(relation1, relation2) );
    }

    // Display the relation
    DisplayRelation displayRelation;
    displayRelation.setModal(true);
    displayRelation.exec();
}
