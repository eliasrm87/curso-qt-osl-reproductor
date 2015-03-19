// Aplicación realizada por Adrián Rodríguez Bazaga
// alu0100826456@ull.edu.es
// Curso de QT: Reproductor


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
