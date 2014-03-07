#include "qdialogmensaje.h"



QDialogMensaje::QDialogMensaje(QString mensaje, QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Acerca de...");

    this->setGeometry(30, 30, 400, 300);

    etiqueta_ = new QLabel(this);

    etiqueta_->setText(mensaje);//Se establece el mensaje de la etiqueta.

    layout_ = new QGridLayout(this);

    layout_->addWidget(etiqueta_);//Se añade la etiqueta al layout.

    this->setLayout(layout_); //Se estable el layout creado como layout de la ventana.

}


