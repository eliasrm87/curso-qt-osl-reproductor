#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetadataDialog::MetadataDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataDialog)
{
    ui->setupUi(this);

    foreach(QString key, player->availableMetaData()) {
     ui->listMetadata->insertItem(ui->listMetadata->count(), key + ": " + player->metaData(key).toString());
    }
}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}
