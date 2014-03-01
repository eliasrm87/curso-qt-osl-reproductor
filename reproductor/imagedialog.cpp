#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QMediaPlayer* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    ui->barraContraste->setRange(-100, 100);
    //ui->barraContraste->setValue(player->contrast());
    connect(ui->barraContraste, SIGNAL(sliderMoved(int)), player, SLOT(setContrast(int)));
    connect(player, SIGNAL(contrastChanged(int)), ui->barraContraste, SLOT(setValue(int)));}

ImageDialog::~ImageDialog()
{
    delete ui;
}


void ImageDialog::onBrilloChanged(int brillo) {

}

void ImageDialog::onContrasteChanged(int constraste){

}

void ImageDialog::onSaturacionChanged(int saturacion) {

}
