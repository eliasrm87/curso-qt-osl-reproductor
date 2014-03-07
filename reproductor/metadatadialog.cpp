#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetaDataDialog::MetaDataDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetaDataDialog)
{
    ui->setupUi(this);

    player_ = player;

   addMetadata(QMediaMetaData::VideoCodec);
   addMetadata(QMediaMetaData::VideoBitRate);
   addMetadata(QMediaMetaData::AudioCodec);
   addMetadata(QMediaMetaData::Author);
   addMetadata(QMediaMetaData::AlbumTitle);
   //addMetadata(QMediaMetaData::);

}

MetaDataDialog::~MetaDataDialog()
{
    delete ui;
}

void MetaDataDialog::addMetadata(QString key)
{
    foreach (QString key, player_->availableMetaData()){
    ui->listWidget->insertItem(ui->listWidget->count(),
                               key + player_->metaData(key).toString());}
}



