#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QListWidgetItem *nombre = new QListWidgetItem;
    nombre->setText("Reproductor de video");
    ui->listWidget->insertItem(0, nombre);

    QListWidgetItem *copyright = new QListWidgetItem;
    copyright->setText("Domingo Yeray Rodríguez Martín");
    ui->listWidget->insertItem(1, copyright);

    QListWidgetItem *autor = new QListWidgetItem;
    autor->setText("Curso Qt");
    ui->listWidget->insertItem(2, autor);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
