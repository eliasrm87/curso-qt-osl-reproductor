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
    btnFull_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 6);
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 6);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(btnFull_,      2, 4, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 5, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));
    btnFull_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));


    // Menu
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_ -> addMenu(mnuArchivo_);

    setMenuBar(mainMenu_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    mnuArchivo_ -> addAction(actArchivoSalir_);
    actArchivoSalir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));


    mostrarRecientes();


    mnuAyuda_ = new QMenu(tr("A&yuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcerca_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcerca_);

    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_ -> addMenu(mnuVer_);
    actVerFull_ = new QAction(tr("&Pantall completa"), this);
    mnuVer_->addAction(actVerFull_);
    actVerFull_ -> setShortcut(QKeySequence(Qt::ALT + Qt::Key_F));


    mnuVerMetadatos_ = mnuVer_->addMenu(tr("Meta datos"));
    actMetaDatos_ = new QAction(tr("&Ver meta datos"), this);
    mnuVerMetadatos_ -> addAction(actMetaDatos_);
    //mnuVer_->addAction(actMetaDatos_);
    //actMetaDatos_ ->addAction(dock->toggleViewAction());
    actMetaDatos_ -> setShortcut(QKeySequence(Qt::ALT + Qt::Key_M));


    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(btnFull_,      SIGNAL(pressed()),               this,         SLOT(pantallaCompleta()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actAyudaAcerca_, SIGNAL(triggered()), this, SLOT(acerca()));

    connect(actMetaDatos_, SIGNAL(triggered()), this, SLOT(mostrarMetadata()));

    connect(actVerFull_, SIGNAL(triggered()), this, SLOT(pantallaCompleta()));
    connect(videoWidget_, SIGNAL(mouseDoubleClickEvent(QMouseEvent*)), this, SLOT(pantallaCompleta(QMouseEvent*)));


}

MainWindow::~MainWindow()
{

}


void MainWindow::onOpenURL()
{
    // Para streaming
    //mediaPlayer_->setMedia(QUrl("http://IP:PUETO/xxx"));
}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {
        QFile fileHistorial("historial.txt");
        fileHistorial.open(QIODevice::Append);
        QTextStream out(&fileHistorial);
        out << fileName << endl;
        fileHistorial.close();
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        // Para streaming
        //mediaPlayer_->setMedia(QUrl("http://IP:PUETO/xxx"));
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


void MainWindow::acerca()
 {
    QMessageBox::about(this, tr("Acerca de esta aplicación"),
             tr("Esta <b>Aplicación</b> es un ejemplo hecho "
                "para el curso de QT. <br/> "
                "Eduardo Nacimiento García <br/>"
                "<a href=\"mailto:micorreo@eduardonacimiento.com\">micorreo@eduardonacimiento.com</a>"));
 }


void MainWindow::mostrarMetadata()
 {
    // Metodo 1 con DOCK
    dock_ = new QDockWidget(tr("Meta datos"), this);
    dock_->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QListWidget* metadatosList = new QListWidget(dock_);
    QStringList meta = mediaPlayer_->availableMetaData();
    QStringList datos;
    QString mData;

    foreach (mData, meta) {
        datos.append(mData + ": " + mediaPlayer_->metaData(mData).toString());
    }

    metadatosList->addItems(datos);

    QString key;
    dock_->setWidget(metadatosList);
    addDockWidget(Qt::RightDockWidgetArea, dock_);


    // Metodo 2 con DIALOG
    metadataDialog md(mediaPlayer_);
    md.exec();

 }

void MainWindow::pantallaCompleta(QMouseEvent* event)
 {
     videoWidget_->setFullScreen(!videoWidget_->isFullScreen());
     event->accept();
 }

void MainWindow::pantallaCompleta()
{
    if (videoWidget_->isFullScreen()) {
        videoWidget_->setFullScreen(false);
    }
    else {
        videoWidget_->setFullScreen(true);
    }
}


void MainWindow::mostrarRecientes() {
    QFile file("historial.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    QAction *tmpAction = new QAction(linea, this);
    tmpAction = new QAction(linea, this);
    tmpAction->setData(linea);
    mnuArchivoRecientes_ = mnuArchivo_->addMenu(tr("Recientes"));
    mnuArchivoRecientes_ -> addAction(tmpAction);
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(setReciente()));
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea, this);
        tmpAction->setData(linea);
        mnuArchivoRecientes_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setReciente()));
    }
    file.close();
}

void MainWindow::setReciente () {
    QString nuevo = ((QAction*)QObject::sender())->data().toString();
    qDebug("Abierto reciente");
    mediaPlayer_->setMedia(QUrl::fromLocalFile(nuevo));
}
