#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <iostream>
#include "../Engine.h"
#include "../Player.h"
//#include "../MLSdataTables/"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Engine* engine = new Engine();
    MainWindow::instance().setEngine(engine);
    //engine->open("../MLSdataTables/1.txt");
    return a.exec();
}
