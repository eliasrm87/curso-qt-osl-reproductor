#include "metadatadialog.h"
#include "ui_metadatadialog.h"

metadataDialog::metadataDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::metadataDialog)
{
    ui->setupUi(this);

    foreach (QString key, player->availableMetaData()) {
        ui->listMetadata->insertItem(ui->listMetadata->count(),
                                     key + ": " + player->metaData(key).toString());
    }

}

metadataDialog::~metadataDialog()
{
    delete ui;
}

