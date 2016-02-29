#include "projectrelation.h"
#include "ui_projectrelation.h"
#include "../Engine.h"
#include "mainwindow.h"
#include "displayrelation.h"
#include <QMessageBox>
ProjectRelation::ProjectRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectRelation)
{
    ui->setupUi(this);

    Engine* engine = MainWindow::instance().getEngine();

    for (int i=0; i< engine->getNumRelations(); i++) {
        QString relationName = QString::fromStdString( engine->getRelation(i)->getName() );
        ui->pRelationE->addItem(relationName);
    }

    // Example for Attributes
    ui->pAttributesE->setText("for example, Name, Age, Rush Yard");

}

ProjectRelation::~ProjectRelation()
{
    delete ui;
}

void ProjectRelation::on_buttonBox_accepted()
{
    Engine* engine = MainWindow::instance().getEngine();
    Parser* parser = new Parser();

    // Get relation
    string relation = ui->pRelationE->currentText().toUtf8().constData();

    int relation_index = engine->findRelation(relation);
    if (relation_index == -1) {
        QString errorMessage = QString::fromStdString("Relation not found");
        QMessageBox::information(0, "info", errorMessage);
    }
    else {
        Relation* the_relation = engine->getRelation(relation_index);

        // Get attributes
        string attribute = ui->pAttributesE->text().toUtf8().constData();

        vector<Attribute*> all_attributes = the_relation->getAttributes();
        vector<Attribute*> attributes;

        vector<Token> attTokens = parser->splitInput(attribute);

        // Finding the attributes
        bool all_atts_found = true;
        for (int i=0; i< attTokens.size(); i++) {

            for (int j=0; j< all_attributes.size(); j++) {

                if (attTokens.at(i).getValue() == all_attributes.at(j)->getName()) {
                    attributes.push_back( all_attributes.at(j) );
                    break;
                }

                if (j == all_attributes.size()-1) {
                    string str = "Attribute \"" + attTokens.at(i).getValue() + "\" not found";
                    QString errorMessage = QString::fromStdString(str);
                    QMessageBox::information(0, "info", errorMessage);
                    all_atts_found = false;
                }
            }
        }

        if (all_atts_found) {
            // Run
            Tree*   tree = new Tree();

            MainWindow::instance().setRelation( engine->project(relation, attributes) );

            // Display the relation
            DisplayRelation displayRelation;
            displayRelation.setModal(true);
            displayRelation.exec();
        }
    }
}
