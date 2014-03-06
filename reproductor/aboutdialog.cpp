#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    acercaDe_ = new QLabel;
    acercaDe_->setText(tr("Este reproductor ha sido creado por\n"
                          "David Hernández Bethencourt mediante\n"
                          "el curso de Qt de la OSL."));

    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Close);

    //Conexión de botón de Ok
    connect(buttonBox_, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout_ = new QVBoxLayout;
    mainLayout_->addWidget(acercaDe_);
    mainLayout_->addWidget(buttonBox_);

    this->setLayout(mainLayout_);
    this->setWindowTitle(tr("Acerca de"));
}
