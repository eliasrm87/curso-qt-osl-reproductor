#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetadataDialog::MetadataDialog(QMediaPlayer *player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataDialog)
{
    ui->setupUi(this);

    player_ = player;

    QString mensaje = "No se ha encontrado ningun metadato debido a que\nno se ha abierto ningún vídeo";

    // Si no han cargado el video muestra la duracion
    if (!player_->isVideoAvailable()) {
        ui->listMetadata->insertItem(ui->listMetadata->count(), mensaje);
    }
    else {
        addMetadata(QMediaMetaData::Title);
        addMetadata(QMediaMetaData::AudioCodec);
    }
}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}

void MetadataDialog::addMetadata(QString key)
{
    ui->listMetadata->insertItem(ui->listMetadata->count(),
                                 key + ": " + player_->metaData(key).toString());
}
