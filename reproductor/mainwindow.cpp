#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Centrar ventana en pantalla
    QRect qr = this->frameGeometry();
    qr.moveCenter(QDesktopWidget().availableGeometry().center());
    this->move(qr.topLeft());

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    // Archivo
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    // Archivo > Abrir
    actAbrir_ = new QAction(tr("&Abrir"), this);
    actAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actAbrir_);

    // Archivo > Recientes
    mnuRecientes_ = new QMenu(tr("&Recientes"), this);
    mnuArchivo_->addMenu(mnuRecientes_);

    // Ver
    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_->addMenu(mnuVer_);

    // Ver > Pantalla completa
    actPantallaCompleta_ = new QAction(tr("&Pantalla completa"), this);
    actPantallaCompleta_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    mnuVer_->addAction(actPantallaCompleta_);

    // Ver > Salir pantalla completa
    actSalirPantallaCompleta_ = new QAction(tr("&Salir pantalla completa"), this);
    actSalirPantallaCompleta_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));

    // Ver > Metadatos
    actMetadatos_ = new QAction(tr("&Metadatos"), this);
    actMetadatos_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnuVer_->addAction(actMetadatos_);

    // Ayuda
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    // Ayuda > Acerca de..
    actAcercaDe_ = new QAction(tr("&Acerca de ..."), this);
    actAcercaDe_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    mnuAyuda_->addAction(actAcercaDe_);

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
    connect(actAbrir_,     SIGNAL(triggered()),             this,         SLOT(onOpen()));
    connect(actAcercaDe_,  SIGNAL(triggered()),             this,         SLOT(alAcercaDe()));
    connect(actPantallaCompleta_,  SIGNAL(triggered()),     this,         SLOT(PantallaCompleta()));
    connect(actSalirPantallaCompleta_,  SIGNAL(triggered()),this,         SLOT(SalirPantallaCompleta()));
    connect(actMetadatos_, SIGNAL(triggered()),             this,         SLOT(MetaDatos()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    CargarRecientes();
    mediaPlayer_->availableMetaData();
    this->setMenuBar(mainMenu_);

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
        fileOpen_ = QUrl::fromLocalFile(fileName).toString();
        GuardarDireccionArchivo(fileOpen_);
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

void MainWindow::alAcercaDe(){

     QMessageBox::about(this, "Acerca de ...", "Versión 0.1 Alpha\nCopyright 2014");

}

void MainWindow::PantallaCompleta(){

    videoWidget_->setFullScreen(true);

}

void MainWindow::SalirPantallaCompleta(){
    videoWidget_->setFocus();
    videoWidget_->fullScreenChanged(false);
    videoWidget_->setFullScreen(false);
}

void MainWindow::GuardarDireccionArchivo(QString line){

    QFile file("recientes.txt");
    file.open(QIODevice::Append);

    QTextStream out(&file);

    out << line << endl;
    actReciente_ = new QAction(line, this);
    mnuRecientes_->addAction(actReciente_);
    connect(actReciente_,  SIGNAL(triggered()), this, SLOT(PulsarReciente()));

    /* Close the file */
    file.close();

}

void MainWindow::PulsarReciente(){
    QAction* act = (QAction*) QObject::sender();
    mediaPlayer_->setMedia(QUrl(act->text()));
}

void MainWindow::CargarRecientes(){

    QFile file("recientes.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        actReciente_ = new QAction(line, this);
        mnuRecientes_->addAction(actReciente_);
        connect(actReciente_,  SIGNAL(triggered()), this, SLOT(PulsarReciente()));
    }

    file.close();
}

void MainWindow::MetaDatos(){

    md_ = new MetadataDialog(mediaPlayer_, this);
    md_->exec();

}
