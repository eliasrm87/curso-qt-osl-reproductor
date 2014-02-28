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

    //Menus
    mainMenu_ = new QMenuBar(this);

    menusFile_ = new QMenu(tr("&File"), this );
    mainMenu_ -> addMenu(menusFile_);
    setMenuBar(mainMenu_);

    actionOpenFile_ = new QAction( tr("&Open"),this );
    actionOpenFile_ -> setShortcut( QKeySequence ( Qt::CTRL + Qt::Key_O ) );
    menusFile_ -> addAction(actionOpenFile_);

    actionAbout_ = new QAction ( tr("&About"), this);
    actionAbout_ -> setShortcut( QKeySequence ( Qt::CTRL + Qt::Key_A ) );
    menusFile_ -> addAction(actionAbout_);

    actionFullScreen_ = new QAction ( tr("&FullScren"), this);
    actionFullScreen_ -> setShortcut( QKeySequence ( Qt::CTRL + Qt::Key_F ) );
    menusFile_ ->addAction(actionFullScreen_);

    menusMetadato_ = new QMenu(tr("&Metadata"), this );
    mainMenu_ -> addMenu(menusMetadato_);

    actionShowMetadata = new QAction ( tr("Show Metadata"),this);
    menusMetadato_ -> addAction(actionShowMetadata);


    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    //Connections to menu
    connect( actionOpenFile_, SIGNAL ( triggered() ), this, SLOT(onOpen_auto() ) );
    connect( actionAbout_, SIGNAL( triggered() ), this, SLOT(onAbout() ) );
    connect( actionFullScreen_, SIGNAL( triggered() ), this, SLOT(onFullScreen() ) );

    connect ( actionShowMetadata, SIGNAL(triggered()), this, SLOT( onMetadata() ) );
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    mediaPlayer_->setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM"));
    //Show file open dialog
    //QString fileName = QFileDialog::getOpenFileName(this,
    //                                        tr("Abrir archivo"));
    //if (fileName != "") {
    //    mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
    //}
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


void MainWindow::onAbout()
{
    QMessageBox::about(this,"About","This is a Qt proyect.");
}

void MainWindow::onOpen_auto()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));

    mediaPlayer_->play();

    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        mediaPlayer_->play();
    }
}

void MainWindow::onFullScreen()
{

    if ( videoWidget_->isFullScreen() )
    {
        videoWidget_->setFullScreen(false);
    }
    else
    {
        videoWidget_->setFullScreen(true);
    }
}

void MainWindow::onMetadata()
{
    MetadataDialog md(mediaPlayer_);
    md.exec();
}




