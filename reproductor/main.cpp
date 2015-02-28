#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QLocale locale;
    QTranslator translator;
    translator.load("reproductor_"+locale.bcp47Name());
    a.installTranslator(&translator);



    w.show();
    
    return a.exec();
}
