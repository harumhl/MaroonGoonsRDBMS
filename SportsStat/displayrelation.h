#ifndef DISPLAYRELATION_H
#define DISPLAYRELATION_H

#include <QDialog>

namespace Ui {
class DisplayRelation;
}

class DisplayRelation : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayRelation(QWidget *parent = 0);
    ~DisplayRelation();

private slots:
    void on_updateButton_clicked();

    void on_renameButton_clicked();

private:
    Ui::DisplayRelation *ui;
};

#endif // DISPLAYRELATION_H
