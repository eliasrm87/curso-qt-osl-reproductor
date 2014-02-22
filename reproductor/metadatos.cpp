#include "metadatos.h"
#include "ui_metadatos.h"

MetadaDatos::MetadaDatos(QMediaPlayer* player,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadaDatos)
{
    ui->setupUi(this);

}

MetadaDatos::~MetadaDatos()
{
    delete ui;
}
