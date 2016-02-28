#include "displayrelation.h"
#include "ui_displayrelation.h"
#include "mainwindow.h"
#include "../Engine.h"

DisplayRelation::DisplayRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayRelation)
{
    ui->setupUi(this);

    Engine* engine = MainWindow::instance().getEngine();
    Relation* relation = MainWindow::instance().getRelation();

    // TEMP
    if (relation == NULL && engine->getNumRelations() > 0)
        relation = engine->getRelation(0);

    // Display relation name
    ui->relationName->setText( QString::fromStdString(relation->getName()) );

    if (relation != NULL) {
        vector<Attribute*> attributes = relation->getAttributes();
        vector<Tuple*> tuples = relation->getTuples();

        ui->tableWidget->setColumnCount( attributes.size() );
        ui->tableWidget->setRowCount( tuples.size() );

        // Setting attribute names (column names/titles)
        for (int i=0; i< attributes.size(); i++) {
            QString attributeName = QString::fromStdString( attributes.at(i)->getName() );
            ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(attributeName));
        }

        // Iterate through each tuple
        for (int i=0; i< tuples.size(); i++) {
            vector<string> contents = tuples.at(i)->getContents();

            for (int j=0; j< contents.size(); j++) {

                QTableWidgetItem* q = new QTableWidgetItem( QString::fromStdString(contents.at(j)) );
                ui->tableWidget->setItem(i, j, q);
            }
        }

        MainWindow::instance().setRelation(NULL);
    }
}

DisplayRelation::~DisplayRelation()
{
    delete ui;
}
