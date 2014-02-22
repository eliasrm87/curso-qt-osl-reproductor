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
    mediaPlayer_  = new QMediaPlayer(this); // Objeto que se encarga del video
    playerSlider_ = new QSlider(Qt::Horizontal, this); // Barra de tiempo de reproducción
    videoWidget_  = new QVideoWidget(this); // Recuadro negro de vídeo
    volumeSlider_ = new QSlider(Qt::Horizontal, this); // Barra de volumen
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_); // Añadir el recuadro al reproductor
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

    // Inicializamos los elementos del menú
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mnuVer_ = new QMenu(tr("&Ver"), this);
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);

    // Añadimos los elementos al menú
    mainMenu_->addMenu(mnuArchivo_);
    mainMenu_->addMenu(mnuVer_);
    mainMenu_->addMenu(mnuAyuda_);

    // Inicializamos acciones de los elementos del menú
    // Añadimos las acciones a los elementos
    // Añadimos los shortcuts correspondientes
    actArchivoAbrir_ = new QAction(tr("Abrir..."), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoRecientes_ = new QAction(tr("Recientes"), this);
    mnuArchivo_->addAction(actArchivoRecientes_);

    actVerPantallaCompleta_ = new QAction(tr("Pantalla completa"), this);
    actVerPantallaCompleta_->setShortcut(QKeySequence(Qt::Key_F11));
    mnuVer_->addAction(actVerPantallaCompleta_);

    actVerMetadatos_ = new QAction(tr("Metadatos"), this);
    mnuVer_->addAction(actVerMetadatos_);

    actAyudaAcercaDe_ = new QAction(tr("Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcercaDe_);

    // Añadir barra de menús a la ventana
    setMenuBar(mainMenu_);

}

MainWindow::~MainWindow()
{

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
