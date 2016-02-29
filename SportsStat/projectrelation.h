#ifndef PROJECTRELATION_H
#define PROJECTRELATION_H

#include <QDialog>

namespace Ui {
class ProjectRelation;
}

class ProjectRelation : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectRelation(QWidget *parent = 0);
    ~ProjectRelation();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ProjectRelation *ui;
};

#endif // PROJECTRELATION_H
