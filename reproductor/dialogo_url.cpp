// Aplicación realizada por Adrián Rodríguez Bazaga
// alu0100826456@ull.edu.es
// Curso de QT: Reproductor


#include "dialogo_url.h"
#include "ui_urldialog.h"

UrlDialog::UrlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UrlDialog)
{
    ui->setupUi(this);

}

UrlDialog::~UrlDialog()
{
    delete ui;
}

QString UrlDialog::getNuevaUrl() {
    url_ = ui->lineEdit->text();
    return url_;
}
