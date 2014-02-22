#include "metadatadialog.h"
#include "ui_metadatadialog.h"

MetadataDialog::MetadataDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetadataDialog)
{
    ui->setupUi(this);
}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}
