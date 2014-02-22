#include "dialogstreaming.h"
#include "ui_dialogstreaming.h"

DialogStreaming::DialogStreaming(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStreaming)
{
    ui->setupUi(this);
}

DialogStreaming::~DialogStreaming()
{
    delete ui;
}
