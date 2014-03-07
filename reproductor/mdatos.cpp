#include "mdatos.h"
#include "ui_mdatos.h"

MDatos::MDatos(QMediaPlayer *player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MDatos)
{

    ui->setupUi(this);
    player_=player;
    foreach (QString key,player_->availableMetaData())
    {
    ui->listWidget->insertItem(ui->listWidget->count(),key +": " +player_->metaData(key).toString());
    }


}

MDatos::~MDatos()
{
    delete ui;
}

