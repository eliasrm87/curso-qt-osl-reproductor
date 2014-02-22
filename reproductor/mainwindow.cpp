#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 5);
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 5);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    //Parte de clase
    //Menú archivo -> abrir
    barMenu_ = new QMenuBar(this);
    setMenuBar(barMenu_);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    barMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    mnuArchivo_->addAction(actArchivoAbrir_);
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(onOpen()));

    //Pantalla completa
    mnuVer_ = new QMenu(tr("&Ver"), this);
    barMenu_->addMenu(mnuVer_);

    actFullScreen_ = new QAction(tr("&Pantalla completa"), this);
    mnuVer_->addAction(actFullScreen_);
    connect(actFullScreen_, SIGNAL(triggered()), this, SLOT(escuchaActFS()));
    connect(this, SIGNAL(fullScreen(bool)), videoWidget_, SLOT(setFullScreen(bool)));
    actFullScreen_->setShortcut(QKeySequence(Qt::Key_F11));
    estadoFS_ = false;

    //Menú ayuda -> acerca de
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    barMenu_->addMenu(mnuAyuda_);

    actAyudaAcerca_ = new QAction(tr("&Acerca De"), this);
    mnuAyuda_->addAction(actAyudaAcerca_);
    connect(actAyudaAcerca_, SIGNAL(triggered()), this, SLOT(onAcercaDe()));

    //Recientes
    mnuRecientes_ = new QMenu(tr("&Recientes"), this);
    mnuArchivo_->addMenu(mnuRecientes_);

    //Ver metadatos
    actVerMetadatos_ = new QAction(tr("&Metadatos"), this);
    mnuVer_->addAction(actVerMetadatos_);
    connect(actVerMetadatos_, SIGNAL(triggered()), this, SLOT(verMetadatos()));

    //QTcpSocket
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //mediaPlayer_->setMedia(QUrl());

    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));

        //Recientes
        JReciente* reciente = new JReciente(this);
        reciente->setURL(fileName);
        mnuRecientes_->addAction(reciente);
        connect(reciente, SIGNAL(pulsado(QString)), this, SLOT(abrirReciente(QString)));
    }
}



void MainWindow::onSeek()
{
    mediaPlayer_->setPosition(playerSlider_->sliderPosition());
}

void MainWindow::onDurationChanged(qint64 duration)
{
    playerSlider_->setRange(0, duration);
}

void MainWindow::onPositionChanged(qint64 position)
{
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}

void MainWindow::onAcercaDe()
{
  JDialog* asd = new JDialog();
  asd->exec();
}

void MainWindow::abrirReciente(QString url)
{
    mediaPlayer_->setMedia(QUrl::fromLocalFile(url));
}

void MainWindow::verMetadatos()
{
    /* QVariant titulo = mediaPlayer_->metaData(QMediaMetaData::Duration);

    QMessageBox dialogo;
    QString texto = titulo.toString();
    dialogo.setText(texto);
    dialogo.exec(); */
    MetadataDialog md (mediaPlayer_);
    md.exec();
}

void MainWindow::escuchaActFS()
{
    if (! estadoFS_) {
        estadoFS_ = true;
        emit fullScreen(true);
    }
    else {
        estadoFS_ = false;
        emit fullScreen(false);
    }

}


