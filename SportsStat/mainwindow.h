#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Engine.h"
#include "../Player.h"
#include "createplayer.h"
#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow& instance() {
        static MainWindow _inst;
        return _inst;
    }
    void newPlayer(Player* cp);

    // My setters and getters
    void setEngine (Engine* e) { engine = e; }
    void setRelation (Relation* r) { relation = r; }
    Engine* getEngine() { return engine; }
    vector<Player*> getPlayerVec() { return playerVec; }
    Relation* getRelation() { return relation; }

private slots:
    void on_ExecuteButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    Engine* engine;
    vector<Player*> playerVec;
    Relation* relation; // temp value
};

#endif // MAINWINDOW_H
