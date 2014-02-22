#include "dialogforstreaming.h"
#include "ui_dialogforstreaming.h"

DialogforStreaming::DialogforStreaming(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogforStreaming)
{
    ui->setupUi(this);

}

DialogforStreaming::~DialogforStreaming()
{
    delete ui;
}

void DialogforStreaming::on_pushOk_clicked()
{
    emit s_enviarUrl(QUrl(edit->text()));
}
