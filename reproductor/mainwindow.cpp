#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Creando los menus.
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);
    mnuAyuda_ = new QMenu(tr("&Ayuda"),this);
    mainMenu_->addMenu(mnuAyuda_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actAcercaDe_ = new QAction(tr("&Acerca de"),this);
    mnuAyuda_->addAction(actAcercaDe_);

    mnuVer = new QMenu(tr("&Ver"),this);
    mainMenu_->addMenu(mnuVer);
    actPantallaCompleta_ = new QAction(tr("&Pantalla completa"),this);
    mnuVer->addAction(actPantallaCompleta_);

    crearVentanaAcercaDe();

    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new myQvideoWidget();
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

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(onOpen()));
    connect(actAcercaDe_,       SIGNAL(triggered()), this,          SLOT(alAcercaDe()));
    connect(actPantallaCompleta_,       SIGNAL(triggered()), this,          SLOT(pantallaCompleta()));

}

MainWindow::~MainWindow()
{
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    mnuArchivo_->deleteLater();
    mnuAyuda_->deleteLater();
    qdAcercaDe_->deleteLater();
}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
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

void MainWindow::alAcercaDe()
{
    qdAcercaDe_->exec();
    //qdAcercaDe_->setGeometry(30, 30, 100, 100);

}

void MainWindow::crearVentanaAcercaDe()
{
    qdAcercaDe_= new QDialog(this);
    qdAcercaDe_->setWindowTitle("Acerca de...");
    layAcercaDe_= new QGridLayout(qdAcercaDe_);
    qdAcercaDe_->setLayout(layAcercaDe_);

    labAcercaDe_ = new QLabel("Reproductor de video hecho en QT.");
    layAcercaDe_->addWidget(labAcercaDe_,0,0,1,1);

}

void MainWindow::pantallaCompleta()
{
    videoWidget_->setFullScreen(true);
}

