#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetadataDialog::MetadataDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataDialog)
{
    ui->setupUi(this);  

    foreach (QString key, player->availableMetaData()){
    ui->listWidget->insertItem(ui->listWidget->count(),
                                key +": "+player->metaData(key).toString());
    }
/*    addMetadatos("Title");
    addMetadatos(QMediaMetaData::VideoCodec);
    addMetadatos(QMediaMetaData::VideoBitRate);
    addMetadatos(QMediaMetaData::AudioCodec);
    addMetadatos(QMediaMetaData::AudioBitRate);
    */
}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}
