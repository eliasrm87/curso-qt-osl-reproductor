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
    menuArchivo_  = new QMenu("Archivo",this);
    menuAyuda_    = new QMenu("Ayuda",this);
    ver_          = new QMenu("Ver",this);
    recientes_    = new QMenu("Recientes",this);
    metadatos_    = new QMenu("Metadatos",this);
    abrir_        = new QAction("Abrir",this);
    AcercaDe_     = new QAction("AcercaDe",this);
    PantCom_      = new QAction("Pantalla Completa",this);
    verMetadatos_ = new QAction("ver metadatos",this);
    str_          = new QAction("video streaming",this);

    //PantCom_->setShortcut(QKeySequence(Qt::ALT+Qt::Key_F));
    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    menuArchivo_->addAction(abrir_);
    menuArchivo_->addAction(str_);
    menuArchivo_->addMenu(recientes_);
    menuAyuda_->addAction(AcercaDe_);
    ver_->addAction(PantCom_);
    metadatos_->addAction(verMetadatos_);
    menuBar()->addMenu(menuArchivo_);
    menuBar()->addMenu(ver_);
    menuBar()->addMenu(metadatos_);
    menuBar()->addMenu(menuAyuda_);



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
    videoWidget_->installEventFilter(this);


    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(abrir_,        SIGNAL(triggered()),             this,         SLOT(onOpen()));
    connect(AcercaDe_,     SIGNAL(triggered()),             this,         SLOT(acercade_s()));
    connect(PantCom_,      SIGNAL(triggered()),             this,         SLOT(fullScreen_s()));
    connect(verMetadatos_, SIGNAL(triggered()),             this,         SLOT(meta_s()));
    connect(str_,          SIGNAL(triggered()),             this,         SLOT(open_str()));

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
    recientes_->addAction(new QAction(fileName,this));
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
void MainWindow::acercade_s()
{
   dialog_=new Dialog();
   dialog_->show();

}
void MainWindow::fullScreen_s()
{
  if(videoWidget_->isFullScreen())
      videoWidget_->setFullScreen(false);
  else
      videoWidget_->setFullScreen(true);
}
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
                    videoWidget_->setFullScreen(false);
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
void MainWindow::open_str()
{
   DialogforStreaming *ds=new DialogforStreaming;
   ds->show();

   connect(ds,SIGNAL(s_enviarUrl(QUrl)),this,SLOT(open_str_url(QUrl)));
   //mediaPlayer_->setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM")); // solo me funciona aqui ??

}
void MainWindow::open_str_url(QUrl url)
{
  mediaPlayer_->setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM"));
  mediaPlayer_->setMedia(QUrl(url));


}

void MainWindow::meta_s()
{
   MDatos md(mediaPlayer_);
   md.exec();

}




