#ifndef DISPLAYHELP_H
#define DISPLAYHELP_H

#include <QDialog>

namespace Ui {
class DisplayHelp;
}

class DisplayHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayHelp(QWidget *parent = 0);
    ~DisplayHelp();

private:
    Ui::DisplayHelp *ui;
};

#endif // DISPLAYHELP_H
