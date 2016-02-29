#include "selectrelation.h"
#include "ui_selectrelation.h"
#include "mainwindow.h"
#include "../Parser.h"
#include "../Parser.cpp"
#include "displayrelation.h"
#include <string>
using namespace std;

SelectRelation::SelectRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectRelation)
{
    ui->setupUi(this);

    Engine* engine = MainWindow::instance().getEngine();

    for (int i=0; i< engine->getNumRelations(); i++) {
        QString relationName = QString::fromStdString( engine->getRelation(i)->getName() );
        ui->sRelationE->addItem(relationName);
    }

    // Example for Attributes
    ui->sAttributesE->setText("for example, Name, Age, Rush Yard");

    // Example for WHERE clause
    ui->sWhereE->setText("for example, Year > 3 OR Name != Henry");
}

SelectRelation::~SelectRelation()
{
    delete ui;
}

void SelectRelation::on_buttonBox_accepted()
{
    Engine* engine = MainWindow::instance().getEngine();
    Parser* parser = new Parser();

    // Get relation name
    string relation = ui->sRelationE->currentText().toUtf8().constData();

    int relation_index = engine->findRelation(relation);
    Relation* the_relation = engine->getRelation(relation_index);

    // Get attributes
    string attribute = ui->sAttributesE->text().toUtf8().constData();

    vector<Attribute*> all_attributes = the_relation->getAttributes();
    vector<Attribute*> attributes;

    vector<Token> attTokens = parser->splitInput(attribute);

    // Finding the attributes
    for (int i=0; i< all_attributes.size(); i++) {

        for (int j=0; j< attTokens.size(); j++) {

            if (all_attributes.at(i)->getName() == attTokens.at(j).getValue())
                attributes.push_back( all_attributes.at(i) );
        }
    }

    // Get WHERE clause
    QString whereClauseQ = ui->sWhereE->text();
    string whereClause = whereClauseQ.toUtf8().constData();

    // Run
    Tree*   tree = new Tree();

    vector<Token> tokens = parser->splitInput(whereClause);

    tree->buildTree(tokens, 0);

    MainWindow::instance().setRelation( engine->select(relation, attributes, tree) );

    // Display the relation
    DisplayRelation displayRelation;
    displayRelation.setModal(true);
    displayRelation.exec();
}
