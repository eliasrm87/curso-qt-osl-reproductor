#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    mainMenu_ = new QMenuBar(this);
    setMenuBar(mainMenu_);

    //Initialize menus
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_ -> addMenu(mnuArchivo_);
    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_ -> addMenu(mnuVer_);
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_ -> addMenu(mnuAyuda_);

    actAbrir_ = new QAction(tr("&Abrir"), this);
    mnuArchivo_->addAction(actAbrir_);
    actRecientes_ = new QMenu(tr("&Recientes"), this);
    mnuArchivo_->addMenu(actRecientes_);

    actFullScreen_ = new QAction(tr("&Pantalla Completa"), this);
    mnuVer_->addAction(actFullScreen_);
    actMetadatos_ = new QAction(tr("&Metadatos"), this);
    mnuVer_->addAction(actMetadatos_);

    actAcercaDe_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAcercaDe_);



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

    //Open Recents Videos
    readRecentsVideos();
    for (int i = 0; i < recentsList.size(); ++i) {
        QAction* tmp = new QAction(tr(recentsList.at(i).toLocal8Bit().constData()), this);
        actRecientes_->addAction(tmp);
        connect(tmp,SIGNAL(triggered()), this, SLOT(PulsarReciente()));
    }


    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    //Menu connections
    connect(actAbrir_, SIGNAL(triggered()), this, SLOT(onOpen()) );
    connect(actAcercaDe_, SIGNAL(triggered()), this, SLOT(alAcercade()));
    connect(actFullScreen_, SIGNAL(triggered()), this, SLOT(alFullScreen()));
    connect(actMetadatos_, SIGNAL(triggered()), this, SLOT(alMetadato()));
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
        saveRecent(QUrl::fromLocalFile(fileName).toString());
    }
}

void MainWindow::saveRecent(QString dirFile)
{
    QFile file("./../recentVideos.txt");
    file.open(QIODevice::Append);
    QTextStream out(&file);
    QString url = dirFile;
    out << endl<< url;

    QAction* tmp = new QAction(url, this);
    actRecientes_->addAction(tmp);
    connect(tmp, SIGNAL(triggered()), this, SLOT(PulsarReciente()));

    file.close();
}

void MainWindow::PulsarReciente() {
    QAction* act = (QAction*) QObject::sender();
    //browser_ -> setAddress(act->text());
    mediaPlayer_->setMedia(QUrl(act->text()));
}

void MainWindow::readRecentsVideos()
{
    QFile file("./../recentVideos.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        recentsList << line;
    }

    file.close();
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

void MainWindow::alAcercade()
{
    AboutDialog a;
    a.exec();
}

void MainWindow::alMetadato()
{
    MetadatosDialog metadatosDialog(mediaPlayer_, this);
    metadatosDialog.exec();
}

void MainWindow::alFullScreen()
{
    videoWidget_->setFullScreen(true);
}
