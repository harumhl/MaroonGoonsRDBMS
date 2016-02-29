#include "displayrelation.h"
#include "ui_displayrelation.h"
#include "mainwindow.h"
#include "../Engine.h"
#include <QMessageBox>

DisplayRelation::DisplayRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayRelation)
{
    ui->setupUi(this);

    Engine* engine = MainWindow::instance().getEngine();
    Relation* relation = MainWindow::instance().getRelation();

    // TEMP
    if (relation == NULL) {
        if (engine->getNumRelations() > 0)
            MainWindow::instance().setRelation( engine->getRelation(0) );
        else {
            QString errorMessage = QString::fromStdString("Relation not found");
            QMessageBox::information(0, "info", errorMessage);
        }
    }
    else { // relation != NULL

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

            // Displaying options for other relations
            Engine* engine = MainWindow::instance().getEngine();

            for (int i=0; i< engine->getNumRelations(); i++) {
                QString relationName = QString::fromStdString( engine->getRelation(i)->getName() );
                ui->relationsBox->addItem(relationName);
            }
        }
    }
}

DisplayRelation::~DisplayRelation()
{
    delete ui;
}

void DisplayRelation::on_updateButton_clicked()
{
    ui->tableWidget->clear(); // empty the table

    Engine* engine = MainWindow::instance().getEngine();

    // Getting the relation
    string relationStr = ui->relationsBox->currentText().toUtf8().constData();
    int relation_index = engine->findRelation(relationStr);
    Relation* relation = engine->getRelation(relation_index);
    MainWindow::instance().setRelation(relation);

    // Display relation name
    ui->relationName->setText( QString::fromStdString(relation->getName()) );

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
}

void DisplayRelation::on_renameButton_clicked()
{
    Engine* engine = MainWindow::instance().getEngine();
    Relation* relation = MainWindow::instance().getRelation();

    // Getting the relation
    string newRelation = ui->relationName->text().toUtf8().constData();

    engine->renameRelation(relation->getName(), newRelation);

    // Updating options for other relations
    ui->relationsBox->clear();
    for (int i=0; i< engine->getNumRelations(); i++) {
        QString relationName = QString::fromStdString( engine->getRelation(i)->getName() );
        ui->relationsBox->addItem(relationName);
    }
}
