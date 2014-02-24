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

    //Inicializamos los menus
    mainMenu_ = new QMenuBar(this); //Pedir memoria para la barra
    mnuArchivo_ = new QMenu(tr("&Archivo"), this); //& para el guión bajo para pulsar con Alt, con this indicamos el padre para que cuando él muera, muera el hijo tb
    mainMenu_ -> addMenu (mnuArchivo_);
    setMenuBar(mainMenu_);

    actArchivoAbrir_ = new QAction (tr("&Abrir"), this);
    actArchivoAbrir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O)); //Opcional
    mnuArchivo_ -> addAction (actArchivoAbrir_);

    actArchivoRecientes_ = new QAction (tr("&Recientes"), this);
    actArchivoRecientes_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R)); //Opcional
    mnuArchivo_ -> addAction (actArchivoRecientes_);

    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_ -> addMenu (mnuVer_);
    setMenuBar(mainMenu_);
    actVerPantallacompleta_ = new QAction(tr("&Pantalla Completa"), this);
    actVerPantallacompleta_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    mnuVer_->addAction(actVerPantallacompleta_);

    actVerMetadatos_ = new QAction(tr("&Metadatos"), this);
    actVerMetadatos_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnuVer_->addAction(actVerMetadatos_);

    actVerMaximaFM_ = new QAction(tr("&MaximaFM"), this);
    actVerMaximaFM_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuVer_->addAction(actVerMaximaFM_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_ -> addMenu (mnuAyuda_);
    setMenuBar(mainMenu_);
    actAyudaAcercade_ = new QAction(tr("&Acerca de"), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    mnuAyuda_->addAction(actAyudaAcercade_);

    //Conexión de nuestros menús con los slots
    connect(actArchivoAbrir_, SIGNAL (triggered()), this, SLOT(onOpen()));
    connect(actArchivoRecientes_, SIGNAL (triggered()), this, SLOT(alRecientes()));
    connect(actAyudaAcercade_, SIGNAL(triggered()), this, SLOT(alAcercade()));
    connect(actVerPantallacompleta_, SIGNAL(triggered()), this, SLOT(alPantallacompleta()));
    connect(actVerMetadatos_, SIGNAL(triggered()), this, SLOT(alMetadatos()));
    connect(actVerMaximaFM_, SIGNAL(triggered()), this, SLOT(alMaximaFM()));
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

void MainWindow::alRecientes() {

}

void MainWindow::alAcercade() {
     QMessageBox mensaje;
     mensaje.setText("Curso QT 2014: Reproductor multimedia");
     mensaje.exec();
}

void MainWindow::alPantallacompleta() {

    if (videoWidget_ -> isFullScreen() == true)
        videoWidget_ -> setFullScreen(false);
    else
        videoWidget_ -> setFullScreen(true);
}

void MainWindow::alMetadatos() {

    //En casa de que estén disponibles, muestro en QMessageBox alguno de los metadatos

    QMessageBox mensaje;

    if (mediaPlayer_ ->isMetaDataAvailable() == true) {

     QString vcodec = "VideoCodec: " + mediaPlayer_ ->metaData(QMediaMetaData::VideoCodec).toString();
     QString vbitrate = "VideoBitRate: " + mediaPlayer_ ->metaData(QMediaMetaData::VideoBitRate).toString();
     QString acodec = "AudioCodec: " + mediaPlayer_ ->metaData(QMediaMetaData::AudioCodec).toString();
     QString abitrate = "AudioBitRate: " + mediaPlayer_ ->metaData(QMediaMetaData::AudioBitRate).toString();
     mensaje.setText(vcodec+"\n"+vbitrate+"\n"+acodec+"\n"+abitrate);
     mensaje.exec();
    }


    //Ejecutamos el MetadataDialog para lanzar alguno de los metadatos en ella
    MetadataDialog md(mediaPlayer_);
    md.exec();


}

void MainWindow::alMaximaFM() {

    /* Para pedir la URL por teclado:
    * Crear el form
    * Añadir el include "" en el fichero.h

    OpenStreaminDialog osd;
    osd.exec();
    mediaPlayer_ -> setMedia(QUrl(osd.getUrl()));
    */

    mediaPlayer_ -> setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM"));
}
