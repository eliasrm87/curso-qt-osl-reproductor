#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Crear el menu

    //Menu Archivo
    mnuArchivo_ = new QMenu("Archivo");
    menuBar()->addMenu(mnuArchivo_);
    actAbrir_ = new QAction ("Abrir", this);
    mnuArchivo_ ->addAction(actAbrir_);
    mnuRecent_ = new QMenu ("Archivos Recientes", this);
    mnuArchivo_ ->addMenu(mnuRecent_);

    actStreaming_ = new QAction ("Reproducir Streaming", this);
    mnuArchivo_ ->addAction(actStreaming_);

    //Menu Ver
    mnuVer_ = new QMenu("Ver");
    menuBar()->addMenu(mnuVer_);
    actFullScreen_ = new QAction ("Full Screen", this);
    mnuVer_ ->addAction(actFullScreen_);
    actMetaData_ = new QAction ("Metadata", this);
    mnuVer_ ->addAction(actMetaData_);


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
    mediaPlayer_->setVolume(75);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(75);

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
    //*****
    connect(actAbrir_, SIGNAL(triggered()), this, SLOT(onOpen()));
    connect(actMetaData_ , SIGNAL(triggered()), this, SLOT(onMetaData()));
    connect(mnuRecent_, SIGNAL(triggered(QAction*)), this, SLOT(onRecentFiles(QAction*)));
    connect(actFullScreen_, SIGNAL(triggered()), this, SLOT(onFullScreen()));
    connect(actStreaming_, SIGNAL(triggered()), this, SLOT(onStreaming()));

    videoWidget_->installEventFilter(this); //Instalar el event filter a este widget
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
//STREAMING
    /*
    OpenStreamingDialog osd;
    osd.exec();
    mediaPlayer_->setMedia(QUrl(osd.getUrl()));*/

    QAction* act = new QAction(fileName, this);
    this->onRecentFiles(act);
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

void MainWindow::onFullScreen()
{
    videoWidget_->setFullScreen(true);
}

//Captura del doble Clic
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
    if (obj == videoWidget_) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            if(mouse->button() == Qt::LeftButton){
                if(!videoWidget_->isFullScreen()){
                    videoWidget_->setFullScreen(true);
                }
                else{
                    videoWidget_-> showNormal();
                    //videoWidget_->setParent(this);
                    //lytMain_->addWidget(videoWidget_,  0, 0, 1, 5);
                }
                return true;
            }
        }
        else{
            return false;
        }
    }
    return false;
}

void MainWindow::onRecentFiles(QAction* path)
{
     mnuRecent_->addAction(path);
}

void MainWindow::onMetaData()
{
    MetaDataDialog md(mediaPlayer_);
    md.exec();
}

void MainWindow::onStreaming()
{
    DialogStreaming st;
    st.exec();
}



