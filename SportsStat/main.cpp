#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <iostream>
#include "../Engine.h"
#include "../Player.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Engine* engine = new Engine();
    MainWindow::instance().setEngine(engine);

    return a.exec();
}
