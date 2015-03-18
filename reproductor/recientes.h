#ifndef RECIENTES_H
#define RECIENTES_H


#include <QFile>
#include <QTextStream>
#include <QDebug>

class Recientes
{
private:
    QFile *file;
    QString n_fichero_;
public:
    Recientes(const QString n_fichero="recientes.txt");
    void addReciente(QString);
    QString readReciente();
    ~Recientes();
};

#endif // RECIENTES_H
