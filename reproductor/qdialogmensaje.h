#ifndef QDIALOGMENSAJE_H
#define QDIALOGMENSAJE_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>

class QDialogMensaje : public QDialog
{
    Q_OBJECT
public:
    //Los parámetros opcionales van al final.
    explicit  QDialogMensaje(QString mensaje, QWidget *parent = 0);


private:

    QLabel *etiqueta_;

    QGridLayout *layout_;


};

#endif // QDIALOGMENSAJE_H
