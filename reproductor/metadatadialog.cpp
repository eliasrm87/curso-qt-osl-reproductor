#include "metadatadialog.h"
#include "ui_metadatadialog.h"

// Constructor
MetadataDialog::MetadataDialog(QMediaPlayer *player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataDialog)
{

    ui->setupUi(this);
    foreach(QString key, player->availableMetaData()){
        ui->listWidget->insertItem(ui->listWidget->count(), key+":"+player->metaData(key).toString());
    }

}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}



