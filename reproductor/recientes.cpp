#include "recientes.h"


Recientes::Recientes(const QString n_fichero):
    n_fichero_(n_fichero)
{
    qDebug()<<"Nombre Fichero:"<<n_fichero;
    file = new QFile(n_fichero_);
}

void Recientes::addReciente(QString dir_file)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
        return;
    QTextStream out(file);
    out << dir_file << "\n";
    file->close();
}

QString Recientes::readReciente()
{
    QString ruta;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    QTextStream in(file);
    if(!in.atEnd())
        ruta = in.readLine();
    file->close();
    return ruta;
}

Recientes::~Recientes()
{
    file->close();
}

