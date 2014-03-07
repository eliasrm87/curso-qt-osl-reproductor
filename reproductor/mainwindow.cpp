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
    setConfig_    = new QSettings;

    //Initilize QMenuBar and components
    mbarMenu_ = new QMenuBar(this);

    mnuFile_ = new QMenu(tr("&File"),this);
    actOpen_ = new QAction(tr("Open"),this);
    mnuFile_->addAction(actOpen_);
    mnuRecents_ = new QMenu(tr("Recents Files"),this);
    mnuFile_->addMenu(mnuRecents_);
    createRecentFiles();

    mnuView_ = new QMenu(tr("&View"),this);
    actFullScreen_ = new QAction(tr("Full Screen"),this);
    mnuView_->addAction(actFullScreen_);

    mbarMenu_->addMenu(mnuFile_);
    mbarMenu_->addMenu(mnuView_);

    setMenuWidget(mbarMenu_);

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

    //Menu Connections
    connect(actOpen_,SIGNAL(triggered()),this,SLOT (onOpen()));
    connect(actFullScreen_,SIGNAL(triggered()),this,SLOT(onFullScreen()));

    videoWidget_->installEventFilter(this);
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

    if(setConfig_ != NULL){
        setConfig_->beginWriteArray("Recents");
        if(lstRecents_.size() == 8)
            setConfig_->setArrayIndex(0);
        else
            setConfig_->setArrayIndex(lstRecents_.size());
        setConfig_->setValue("file",fileName);
        setConfig_->endArray();
        lstRecents_.append(fileName);
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

void MainWindow::onFullScreen()
{
    videoWidget_->setFullScreen(true);
}

void MainWindow::onRecent(QAction* act)
{
    mediaPlayer_->setMedia(QUrl::fromLocalFile(act->text()));
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

void MainWindow::createRecentFiles()
{
    setConfig_ = new QSettings("/home/nad/config.player.ini",QSettings::IniFormat);
    setConfig_->beginReadArray("Recents");
    const QStringList childKeys = setConfig_->allKeys();
    foreach (const QString &childKey, childKeys)
        lstRecents_.append(setConfig_->value(childKey).toString());
    mapperRecents_ = new QSignalMapper(this);
    for(int i=0; i<(lstRecents_.size()-1); i++){
        QAction* act = new QAction(lstRecents_[i],this);
        mnuRecents_->addAction(act);
    }
    connect(mnuRecents_,SIGNAL(triggered(QAction*)),this,SLOT(onRecent(QAction*)));
}
