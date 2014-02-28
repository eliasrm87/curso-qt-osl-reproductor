#include "urldialog.h"
#include "ui_urldialog.h"

URLDialog::URLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::URLDialog)
{
    ui->setupUi(this);
}

URLDialog::~URLDialog()
{
    delete ui;
}

QString URLDialog::getUrl()
{
    return ui->lineEdit->text();
}
