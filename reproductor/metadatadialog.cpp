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
        metadatosDisponibles_ = player_->availableMetaData();
        addMetadata(metadatosDisponibles_);
    }
}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}

void MetadataDialog::addMetadata(QStringList metadatos)
{
    QString dato;
    foreach (dato, metadatos) {
        ui->listMetadata->insertItem(ui->listMetadata->count(),
                                     dato + ": " + player_->metaData(dato).toString());
    }

}
