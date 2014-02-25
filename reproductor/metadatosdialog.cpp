#include "metadatosdialog.h"
#include "ui_metadatosdialog.h"

MetadatosDialog::MetadatosDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadatosDialog)
{
    ui->setupUi(this);

    QString titleString = player->metaData(QMediaMetaData::AudioBitRate).toString();
    QListWidgetItem *title = new QListWidgetItem;
    title->setText(titleString);
    ui->listWidget->insertItem(ui->listWidget->count(), title);
}

MetadatosDialog::~MetadatosDialog()
{
    delete ui;
}


