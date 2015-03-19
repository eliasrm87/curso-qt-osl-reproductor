// Aplicación realizada por Adrián Rodríguez Bazaga
// alu0100826456@ull.edu.es
// Curso de QT: Reproductor


#include "dialogo_imagen.h"
#include "ui_imagedialog.h"


ImageDialog::ImageDialog(QMediaPlayer* player, QVideoWidget *video,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    ui->barraContraste->setRange(-100, 100);
    ui->barraContraste->setValue(video->contrast());
    video->setContrast(100);
    video->update();
    qDebug() << "Contraste: " << video->contrast();
    connect(ui->barraContraste, SIGNAL(sliderMoved(int)), this, SLOT(video->setContrast(int)));
    connect(video, SIGNAL(contrastChanged(int)), ui->barraContraste, SLOT(setValue(int)));


    ui->barraContraste->setValue(int(video->contrast() * SLIDER_RANGE));


    ui->barraBrillo->setRange(-100, 100);
    ui->barraBrillo->setValue(video->contrast());
    connect(ui->barraBrillo, SIGNAL(sliderMoved(int)), video, SLOT(setBrightness(int)));
    connect(player, SIGNAL(contrastChanged(int)), ui->barraContraste, SLOT(setValue(int)));

    ui->barraSaturacion->setRange(-100, 100);
    ui->barraSaturacion->setValue(video->contrast());
    connect(ui->barraSaturacion, SIGNAL(sliderMoved(int)), video, SLOT(setSaturation(int)));
    connect(player, SIGNAL(contrastChanged(int)), ui->barraSaturacion, SLOT(setValue(int)));

}

ImageDialog::~ImageDialog()
{
    delete ui;
}
