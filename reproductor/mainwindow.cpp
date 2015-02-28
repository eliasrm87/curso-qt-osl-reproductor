#include "mainwindow.h"
#include <QList>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Create menus and actions
    mainMenu_ = new QMenuBar(this);
    fileMenu_ = new QMenu(tr("&Archivo"), this);
    recentMenu_ = new QMenu(tr("Archivos recientes"), this);

    viewMenu_ = new QMenu(tr("&Ver"), this);
    helpMenu_ = new QMenu(tr("&Ayuda"), this);

    setMenuBar(mainMenu_);
    mainMenu_->addMenu(fileMenu_);
    mainMenu_->addMenu(viewMenu_);
    mainMenu_->addMenu(helpMenu_);

    openAct_ = new QAction(tr("&Abrir..."), this);
    recentFiles_ = new QActionGroup(this);
    fullscreenAct_ = new QAction(tr("&Pantalla completa"), this);
    metadataAct_ = new QAction(tr("&Metadatos..."), this);
    aboutAct_ = new QAction(tr("&Acerca de..."), this);

    fileMenu_->addAction(openAct_);
    fileMenu_->addMenu(recentMenu_);
    viewMenu_->addAction(fullscreenAct_);
    viewMenu_->addAction(metadataAct_);
    helpMenu_->addAction(aboutAct_);

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

    // Actions connections
    connect(openAct_,       SIGNAL(triggered()),         this, SLOT(onOpen()));
    connect(recentFiles_,   SIGNAL(triggered(QAction*)), this, SLOT(onOpenRecent(QAction*)));
    connect(fullscreenAct_, SIGNAL(triggered()),         this, SLOT(onFullScreen()));
    connect(metadataAct_,   SIGNAL(triggered()),         this, SLOT(onMetadataTriggered()));
    connect(aboutAct_,      SIGNAL(triggered()),         this, SLOT(onAboutTriggered()));

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::addRecentFile(QString fileName) {
    QAction* fileAct = new QAction(fileName, this);

    QList<QAction*> recent = recentFiles_->actions();
    for (QList<QAction*>::iterator i = recent.begin(); i != recent.end(); ++i) {
        if ((*i)->text() == fileName)
            return;
    }

    recentMenu_->addAction(fileAct);
    recentFiles_->addAction(fileAct);
}

void MainWindow::openFile(QString fileName) {
    if (!fileName.isEmpty()) {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        addRecentFile(fileName);
    }
}

void MainWindow::onOpen() {
    //Show file open dialog
    openFile(QFileDialog::getOpenFileName(this, tr("Abrir archivo")));
}

void MainWindow::onSeek() {
    mediaPlayer_->setPosition(playerSlider_->sliderPosition());
}

void MainWindow::onDurationChanged(qint64 duration) {
    playerSlider_->setRange(0, duration);
}

void MainWindow::onPositionChanged(qint64 position) {
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume) {
    mediaPlayer_->setVolume(volume);
}

void MainWindow::onOpenRecent(QAction* act) {
    openFile(act->text());
}

void MainWindow::onFullScreen() {
    videoWidget_->setFullScreen(!videoWidget_->isFullScreen());
}

void MainWindow::onMetadataTriggered() {
    QStringList metadataProperties = mediaPlayer_->availableMetaData();

    if (metadataProperties.empty()) {
        QMessageBox::information(this, tr("No hay metadatos"),
                                 tr("No hay metadatos disponibles en el fichero actual"));
        return;
    }

    QStringList metadata;
    for (QStringList::iterator str = metadataProperties.begin(); str != metadataProperties.end(); ++str) {
        QVariant data = mediaPlayer_->metaData(*str);
        metadata.append(*str + ": " + data.toString());
    }

    QLayout* metadataLayout = new QGridLayout(this);
    QDialog* metadataDialog = new QDialog(this);
    QLabel* dialogText = new QLabel(metadata.join("\n"), this);

    metadataLayout->addWidget(dialogText);
    metadataDialog->setLayout(metadataLayout);
    metadataDialog->setWindowTitle(tr("Metadatos"));

    metadataDialog->setModal(true);
    metadataDialog->setVisible(true);
    metadataDialog->exec();
}

void MainWindow::onAboutTriggered() {
    QGridLayout* metadataLayout = new QGridLayout(this);
    QDialog* metadataDialog = new QDialog(this);

    QLabel* image = new QLabel(this);
    image->setPixmap(QPixmap(":/images/resources/qt.jpg"));
    QLabel* dialogText = new QLabel(tr("Hecho por Sergio Afonso"), this);

    metadataLayout->addWidget(image, 0, 0, 1, 1);
    metadataLayout->addWidget(dialogText, 0, 1, 1, 1);
    metadataDialog->setLayout(metadataLayout);
    metadataDialog->setWindowTitle(tr("Metadatos"));

    metadataDialog->setModal(true);
    metadataDialog->setVisible(true);
    metadataDialog->exec();
}
