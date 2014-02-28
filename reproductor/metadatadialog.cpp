#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetaDataDialog::MetaDataDialog(QMediaPlayer *player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetaDataDialog)
{
    ui->setupUi(this);

    foreach (QString key, player->availableMetaData()) {
         ui->listMetadata->insertItem(ui->listMetadata->count(),key +":"+ player->metaData(key).toString());

    }
}

MetaDataDialog::~MetaDataDialog()
{
    delete ui;
}
