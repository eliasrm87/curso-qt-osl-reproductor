#include "imagedialog.h"
#include "ui_imagedialog.h"


ImageDialog::ImageDialog(QMediaPlayer *player, QVideoWidget *video,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    ui->barraContraste->setRange(-100, 100);
    ui->barraContraste->setValue(video->contrast());
    video->setContrast(100);
    qDebug() << "Contraste: " << video->contrast();
    connect(ui->barraContraste, SIGNAL(sliderMoved(int)), video, SLOT(setContrast(int)));
   // connect(video, SIGNAL(contrastChanged(int)), ui->barraContraste, SLOT(setValue(int)));

    ui->barraContraste->setValue(int(video->contrast() * SLIDER_RANGE));


   // ui->barraBrillo->setRange(-100, 100);
    //ui->barraBrillo->setValue(player->contrast());
    connect(ui->barraBrillo, SIGNAL(sliderMoved(int)), video, SLOT(setBrightness(int)));
   // connect(player, SIGNAL(contrastChanged(int)), ui->barraContraste, SLOT(setValue(int)));

    //ui->barraSaturacion->setRange(-100, 100);
    //ui->barraSaturacion->setValue(player->contrast());
    connect(ui->barraSaturacion, SIGNAL(sliderMoved(int)), video, SLOT(setSaturation(int)));
   // connect(player, SIGNAL(contrastChanged(int)), ui->barraSaturacion, SLOT(setValue(int)));

}

ImageDialog::~ImageDialog()
{
    delete ui;
}
