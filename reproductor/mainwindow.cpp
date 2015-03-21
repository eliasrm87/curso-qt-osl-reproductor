#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("KKVLC"));

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actArchivoAbrir_->setIcon(QPixmap(":/icons/resources/open.png"));

    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoStreaming_ = new QAction(tr("Abrir &streaming"), this);
    actArchivoStreaming_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actArchivoStreaming_ ->setIcon(QIcon(":/icons/resources/play.png"));
    mnuArchivo_->addAction(actArchivoStreaming_);

    actArchivoFullScreen_ = new QAction(tr("&Pantalla completa"), this);
    actArchivoFullScreen_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    actArchivoFullScreen_->setIcon(QPixmap(":/icons/resources/fullscreen.png"));

    mnuArchivo_->addAction(actArchivoFullScreen_);

    actArchivoRecientes_ = new QAction(tr("Ver archivos &recientes"), this);
    actArchivoRecientes_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    actArchivoRecientes_->setIcon(QPixmap(":/icons/resources/magnifier.png"));

    mnuArchivo_->addAction(actArchivoRecientes_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QPixmap(":/icons/resources/exit.png"));

    mnuArchivo_->addAction(actArchivoSalir_);

    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_->addMenu(mnuVer_);

    actVerMetadata_ = new QAction(tr("&Metadata"), this);
    actVerMetadata_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    actVerMetadata_->setIcon(QPixmap(":/icons/resources/metadata.png"));

    mnuVer_->addAction(actVerMetadata_);

    listaRecientes_ = new QListWidget();

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("Ac&erca de este editor"), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    actAyudaAcercade_->setIcon(QPixmap(":/icons/resources/help.png"));
    mnuAyuda_->addAction(actAyudaAcercade_);

    this->setMenuBar(mainMenu_);

    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Venta de acerca de con QDialog
    wgtAcercade_ = new QDialog(wgtMain_);
    lytAcercade_ = new QGridLayout(wgtAcercade_);
    wgtAcercade_->setLayout(lytAcercade_);

    listaRecientes_ = new QListWidget();
    playlist_ = new QMediaPlaylist();

    //Initialize widgets
    mediaPlayer_    = new QMediaPlayer(this);
    playerSlider_   = new QSlider(Qt::Horizontal, this);
    videoWidget_    = new QVideoWidget(this);
    volumeSlider_   = new QSlider(Qt::Horizontal, this);
    btnOpen_        = new QToolButton(this);
    btnPlay_        = new QToolButton(this);
    btnPause_       = new QToolButton(this);
    btnStop_        = new QToolButton(this);
    btnFullScreen_  = new QToolButton(this);
    btnRepeat_      = new QToolButton(this);
    btnShuffle_     = new QToolButton(this);


    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,       0, 0, 1, 8);
    lytMain_->addWidget(playerSlider_,      1, 0, 1, 8);
    lytMain_->addWidget(btnOpen_,           2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,           2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,          2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,           2, 3, 1, 1);
    lytMain_->addWidget(btnRepeat_,         2, 4, 1, 1);
    lytMain_->addWidget(btnShuffle_,        2, 5, 1, 1);
    lytMain_->addWidget(btnFullScreen_,     2, 6, 1, 1);
    lytMain_->addWidget(volumeSlider_,      2, 7, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));
    btnRepeat_->setIcon(QIcon(QPixmap(":/icons/resources/repeat.png")));
    btnShuffle_->setIcon(QIcon(QPixmap(":/icons/resources/shuffle.png")));
    btnFullScreen_->setIcon(QIcon(QPixmap(":/icons/resources/fullscreen.png")));



    //Connections
    connect(btnOpen_,               SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(actArchivoAbrir_,       SIGNAL(triggered()),             this,         SLOT(onOpen()));
    connect(actArchivoFullScreen_,  SIGNAL(triggered()),             this,         SLOT(onFullScreen()));
    connect(actAyudaAcercade_,      SIGNAL(triggered()),             this,         SLOT(onAcercade()));
    connect(actArchivoSalir_,       SIGNAL(triggered()),             this,         SLOT(onExit()));
    connect(actArchivoRecientes_,   SIGNAL(triggered()),             this,         SLOT(onRecientes()));
    connect(actVerMetadata_,        SIGNAL(triggered()),             this,         SLOT(onMetadata()));
    connect(actArchivoStreaming_,   SIGNAL(triggered()),             this,         SLOT(onStreaming()));
    connect(btnPlay_,               SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,              SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,               SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(btnRepeat_,             SIGNAL(pressed()),               this,         SLOT(onRepeat()));
    connect(btnFullScreen_,         SIGNAL(pressed()),               this,         SLOT(onFullScreen()));
    connect(playerSlider_,          SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,           SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,           SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_,          SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    createActions();
    createTrayIcon();
}

void MainWindow::createActions()
 {
     minimizeAction = new QAction(tr("Mi&nimize"), this);
     connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

     maximizeAction = new QAction(tr("Ma&ximize"), this);
     connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

     restoreAction = new QAction(tr("&Restore"), this);
     connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
 }

 void MainWindow::createTrayIcon()
 {
     trayIconMenu = new QMenu(this);
     trayIconMenu->addAction(minimizeAction);
     trayIconMenu->addAction(maximizeAction);
     trayIconMenu->addAction(restoreAction);
     trayIconMenu->addSeparator();
     trayIconMenu->addAction(actArchivoSalir_);

     trayIcon = new QSystemTrayIcon(this);
     trayIcon->setContextMenu(trayIconMenu);

     QIcon icon = QIcon(":/icons/resources/play.png");
     trayIcon->setIcon(icon);
     trayIcon->show();
 }

MainWindow::~MainWindow()
{
    mainMenu_->deleteLater();
    btnOpen_->deleteLater();
}

void MainWindow::onOpen()
{
    //Show file open dialog
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
    }
    //Reproducir el vídeo cuando se abre
    mediaPlayer_->play();

    add2Recientes(fileName);
}

void MainWindow::onExit()
{
    close();
}


void MainWindow::onMetadata()
{
    QString metadatos = "";
    if (fileName != "") {
        QMediaResource mr(QUrl::fromLocalFile(fileName));
        QMediaContent mc(mr);
        foreach (QString md, mediaPlayer_->availableMetaData()){
            qDebug() << md << ": " << mediaPlayer_->metaData(md);
            metadatos += md;
            metadatos += ": ";
            metadatos += mediaPlayer_->metaData(md).toString();
            metadatos += "\n";
        }
    } else {
        metadatos += "Ningún fichero abierto. No hay metadatos";
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle("Metadatos");
    msgBox.setText(metadatos);
    msgBox.exec();

}

void MainWindow::onAcercade()
{
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Acerca de");
    wgtAcercade_ = new QWidget(this);
    lytAcercade_ = new QGridLayout(wgtAcercade_);
    dialog->setLayout(lytAcercade_);

    QLabel *imgAcercade_ = new QLabel();
    imgAcercade_ ->setBackgroundRole(QPalette::Dark);
    imgAcercade_ ->setScaledContents(true);

    QPixmap pix(":/icons/resources/help.png");
    imgAcercade_ ->setPixmap(pix);
    lytAcercade_->addWidget(imgAcercade_ , 0, 0);

    QLabel *txtAcercade_ = new QLabel;
    txtAcercade_->setTextFormat(Qt::RichText);
    txtAcercade_->setText("Adrián Rodríguez Vargas");

    lytAcercade_->addWidget(txtAcercade_, 1, 0);

    dialog->show();
    dialog->resize(180, 250);
}

void MainWindow::onStreaming() {
    bool ok;
    //Pedimos la url del multimedia con un qinputdialog
    QString text = QInputDialog::getText(this, tr("Abrir streaming"),tr("URL:"), QLineEdit::Normal,"", &ok);
    if (ok){
        mediaPlayer_->setMedia(QUrl(text));
        //Reproducir el vídeo cuando se abre
        mediaPlayer_->play();
    }
}

void MainWindow::add2Recientes(QString filename){
    QFile archivo;
    archivo.setFileName("recientes.txt");
    if (archivo.open(QFile::WriteOnly | QFile::Append)) {
        archivo.write(filename.toUtf8());
        archivo.write("\n");
        archivo.close();
    }
    onRecientes();
}

void MainWindow::onRecientes() {
    listaRecientes_->clear();
    listaRecientes_->setVisible(true);
    QFile archivo("recientes.txt");
    if (archivo.open(QFile::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            QString Line = in.readLine();
            listaRecientes_->addItem(new QListWidgetItem(Line));
            connect(listaRecientes_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(Play_recientes(QListWidgetItem *)));
        }
        archivo.close();
    }
}

void MainWindow::onRepeat()
{
   if (playlist_->playbackMode() != QMediaPlaylist::Loop){
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);
    btnRepeat_->setCheckable(true);
   }
   else{
    playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
    btnRepeat_->setCheckable(false);
   }
}

void MainWindow::onShuffle()
{
    if (playlist_->playbackMode() != QMediaPlaylist::Random){
        playlist_->setPlaybackMode(QMediaPlaylist::Random);
        btnShuffle_->setCheckable(true);
       }
    else{
        playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
        btnShuffle_->setCheckable(true);
       }
}

void MainWindow::onFullScreen()
{
    videoWidget_->setFullScreen(true);
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
