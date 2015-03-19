// Aplicación realizada por Adrián Rodríguez Bazaga
// alu0100826456@ull.edu.es
// Curso de QT: Reproductor


#include "mainwindow.h"
#include "dialogo_url.h"
#include "dialogo_imagen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Crear widget central y layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Inicializar widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Vertical, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);
    btnFull_      = new QToolButton(this);
    btnRepeat_      = new QToolButton(this);
    btnSecuential_      = new QToolButton(this);
    btnRandom_      = new QToolButton(this);

    icon_ = QPixmap(":/icons/resources/play.png");

    //Configuración de los widgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    videoWidget_->setUpdatesEnabled(true);

    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Añador widgets al gridlayout
    lytMain_->addWidget(videoWidget_,     0, 0, 1, 10);
    lytMain_->addWidget(playerSlider_,    1, 0, 1, 9);
    lytMain_->addWidget(volumeSlider_,    1, 9, 2, 1);
    lytMain_->addWidget(btnOpen_,         2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,         2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,        2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,         2, 3, 1, 1);
    lytMain_->addWidget(btnFull_,         2, 4, 1, 1);
    lytMain_->addWidget(btnRepeat_,       2, 6, 1, 1);
    lytMain_->addWidget(btnSecuential_,   2, 7, 1, 1);
    lytMain_->addWidget(btnRandom_,       2, 8, 1, 1);



    //Iconos de los botones
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));
    btnFull_->setIcon(QIcon(QPixmap(":/icons/resources/fullscreen.png")));
    btnRepeat_->setIcon(QIcon(QPixmap(":/icons/resources/repeat.png")));
    btnSecuential_->setIcon(QIcon(QPixmap(":/icons/resources/secuential.png")));
    btnRandom_->setIcon(QIcon(QPixmap(":/icons/resources/random.png")));


    // Menu
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_ -> addMenu(mnuArchivo_);

    setMenuBar(mainMenu_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    mnuArchivo_ -> addAction(actArchivoSalir_);
    actArchivoSalir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    actArchivoAbrir_ = new QAction(tr("&Abrir archivo"), this);
    mnuArchivo_ -> addAction(actArchivoAbrir_);
    actArchivoAbrir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

    actArchivoUrl_ = new QAction(tr("&Abrir url"), this);
    mnuArchivo_ -> addAction(actArchivoUrl_);
    actArchivoUrl_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));

    actArchivoPlaylist_ = new QAction(tr("&Abrir lista de reproducción"), this);
    mnuArchivo_ -> addAction(actArchivoPlaylist_);
    actArchivoPlaylist_ -> setShortcut(QKeySequence(Qt::ALT + Qt::Key_P));

    mostrarRecientes();


    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcerca_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcerca_);

    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_ -> addMenu(mnuVer_);
    actVerFull_ = new QAction(tr("&Pantalla completa"), this);
    mnuVer_->addAction(actVerFull_);
    actVerFull_ -> setShortcut(QKeySequence(Qt::ALT + Qt::Key_F));

    actVerImagen_ = new QAction(tr("&Propiedades de imagen"), this);
    mnuVer_->addAction(actVerImagen_);

    mnuVerMetadatos_ = mnuVer_->addMenu(tr("Meta datos"));
    actMetaDatos_ = new QAction(tr("&Ver meta datos"), this);
    mnuVerMetadatos_ -> addAction(actMetaDatos_);
    actMetaDatos_ -> setShortcut(QKeySequence(Qt::ALT + Qt::Key_M));

    verSubtitulos();


    //Conexiones
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(btnFull_,      SIGNAL(pressed()),               this,         SLOT(pantallaCompleta()));

    connect(btnRepeat_,       SIGNAL(pressed()),               this,         SLOT(reproducirRepeat()));
    connect(btnSecuential_,   SIGNAL(pressed()),               this,         SLOT(reproducirSecuential()));
    connect(btnRandom_,       SIGNAL(pressed()),               this,         SLOT(reproducirRandom()));

    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actArchivoUrl_, SIGNAL(triggered()), this, SLOT(onOpenURL()));
    connect(actArchivoPlaylist_, SIGNAL(triggered()), this, SLOT(onOpenPlaylist()));
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(onOpen()));

    connect(actAyudaAcerca_, SIGNAL(triggered()), this, SLOT(acerca()));

    connect(actMetaDatos_, SIGNAL(triggered()), this, SLOT(mostrarMetadata()));

    connect(actVerFull_, SIGNAL(triggered()), this, SLOT(pantallaCompleta()));
    connect(actVerImagen_, SIGNAL(triggered()), this, SLOT(propiedadesImagen()));
    connect(videoWidget_, SIGNAL(mouseDoubleClickEvent(QMouseEvent*)), this, SLOT(pantallaCompleta(QMouseEvent*)));


    this->setWindowIcon(icon_);
    setIcon();

}

MainWindow::~MainWindow()
{

}


void MainWindow::onOpenURL()
{
    UrlDialog ud(this);
    ud.exec();
    qDebug() << ud.getNuevaUrl();
    // Para streaming
    mediaPlayer_->setMedia(QUrl(ud.getNuevaUrl()));
    mediaPlayer_->play();

}

void MainWindow::onOpen()
{
    //Dialogo para abrir archivo
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {
        QFile fileHistorial("historial.txt");
        fileHistorial.open(QIODevice::Append);
        QTextStream out(&fileHistorial);
        out << fileName << endl;
        fileHistorial.close();
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        mediaPlayer_->play();
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
    QMessageBox::about(this, tr("Acerca de"),
             tr("Aplicación realizada por:"
                "<b>Adrián Rodríguez Bazaga</b><br/> "
                "Entrega 2: Reproductor <br/>"
                "<a href=\"mailto:alu0100826456@ull.edu.es\">alu0100826456@ull.edu.es</a>"));
 }


void MainWindow::mostrarMetadata()
 {
    // Utilizando el Dock
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
    qDebug("Abierto recientetemente");
    mediaPlayer_->setMedia(QUrl::fromLocalFile(nuevo));
    mediaPlayer_->play();
}



void MainWindow::propiedadesImagen () {
    ImageDialog id(mediaPlayer_, videoWidget_);
    id.exec();

    videoWidget_->update();
    videoWidget_->repaint();

}

void MainWindow::onOpenPlaylist() {
    //Dialogo para abrir archivo
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {

        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&file);
        playlist_ = new QMediaPlaylist;

        dock_ = new QDockWidget(tr("Lista de reproducción"), this);
        dock_->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        QListWidget* playlistLW = new QListWidget(dock_);


        QString linea = in.readLine();
        if (linea != "#EXTM3U") {
            return;
        }
        QString nombre = in.readLine();
        linea = in.readLine();
        playlist_->addMedia(QUrl::fromLocalFile(linea));
        playlistLW->addItem(nombre.mid(8));
        while (!in.atEnd()) {
            nombre = in.readLine();
            linea = in.readLine();
            playlist_->addMedia(QUrl::fromLocalFile(linea));
            playlistLW->addItem(nombre.mid(8));
        }
        playlist_->setCurrentIndex(1);

        dock_->setWidget(playlistLW);
        addDockWidget(Qt::RightDockWidgetArea, dock_);


        mediaPlayer_->setPlaylist(playlist_);
        mediaPlayer_->play();
    }
}


void MainWindow::reproducirRepeat() {
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);
}

void MainWindow::reproducirSecuential() {
    playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
}

void MainWindow::reproducirRandom() {
    playlist_->setPlaybackMode(QMediaPlaylist::Random);
}



void MainWindow::verSubtitulos () {
    QLabel *label = new QLabel(videoWidget_);
    label->setGeometry(10, videoWidget_->width() - 50, videoWidget_->width() - 20, 25);
    label->setAlignment(Qt::AlignHCenter);
    label->setStyleSheet("background-color: rgba(255, 255, 255, 90); color: white; font-weight:bold;");
    label->setText("Aquí van los subtítulos");
}


void MainWindow::setIcon()
{
      //Icono de bandeja del sistema
      trayIcon_ = new QSystemTrayIcon(icon_, this);
      trayIcon_->setToolTip(tr("Reproductor QT"));
      trayIcon_->show();
}
