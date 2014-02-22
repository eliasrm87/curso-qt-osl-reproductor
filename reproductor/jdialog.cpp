#include "jdialog.h"

JDialog::JDialog(QWidget *parent) :
    QDialog(parent) {
    aceptar_ = new QPushButton("Aceptar", this);
    layout_ = new QGridLayout;

    QLabel* etiqueta = new QLabel("Hecho en el curso de la OSL-ULL");
    layout_->addWidget(etiqueta, 0, 0, 1, 1);
    layout_->addWidget(aceptar_, 1, 0, 1, 1);

    setLayout(layout_);

    connect(aceptar_, SIGNAL(pressed()), this, SLOT(close()));
}
