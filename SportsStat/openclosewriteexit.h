#ifndef OPENCLOSEWRITEEXIT_H
#define OPENCLOSEWRITEEXIT_H

#include <QDialog>

namespace Ui {
class OpenCloseWriteExit;
}

class OpenCloseWriteExit : public QDialog
{
    Q_OBJECT

public:
    explicit OpenCloseWriteExit(QWidget *parent = 0);
    ~OpenCloseWriteExit();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OpenCloseWriteExit *ui;
};

#endif // OPENCLOSEWRITEEXIT_H
