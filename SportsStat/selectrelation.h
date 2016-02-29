#ifndef SELECTRELATION_H
#define SELECTRELATION_H

#include <QDialog>

namespace Ui {
class SelectRelation;
}

class SelectRelation : public QDialog
{
    Q_OBJECT

public:
    explicit SelectRelation(QWidget *parent = 0);
    ~SelectRelation();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SelectRelation *ui;
};

#endif // SELECTRELATION_H
