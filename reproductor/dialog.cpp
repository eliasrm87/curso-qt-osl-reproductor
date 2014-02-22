#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Programa de reproducción de video.\n Curso de QT ");
}

Dialog::~Dialog()
{
    delete ui;
}
