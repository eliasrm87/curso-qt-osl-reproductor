#include "metadadialog.h"
#include "ui_metadadialog.h"

metadaDialog::metadaDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::metadaDialog)
{    
    ui->setupUi(this);

    this->setWindowTitle("Metadatos");

    //Se recorren todos los metadatos disponible para el archivo cargado en el reproductot
    // y se añade como items en el QListWidget.
    foreach (QString key, player->availableMetaData())
    {

        //listMetada es un objeto de tipo QListWidget que se ha creado en el diseñador.
        //Se añade un item al QListWidget.

        ui->listMetada->insertItem(ui->listMetada->count(), key + ": " + player->metaData(key).toString());

    }

}

metadaDialog::~metadaDialog()
{
    delete ui;
}

