#include "openstreamingdialog.h"
#include "ui_openstreamingdialog.h"

openStreamingDialog::openStreamingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::openStreamingDialog)
{
    ui->setupUi(this);
}

openStreamingDialog::~openStreamingDialog()
{
    delete ui;
}

//Método que devuelve la url que se ha escrito en txtURL.
QString openStreamingDialog::getURL()
{
    return ui->txtURL ->text();
}
