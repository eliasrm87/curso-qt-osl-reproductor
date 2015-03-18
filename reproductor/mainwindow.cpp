#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Set Title
    this->setWindowTitle(tr("Reproductor --"));

    //Set Menu
    mainMenu_ = new QMenuBar(this);

    //Archivo
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actRecientes_ = new QAction(tr("&Abrir Recientes"), this);
    mnuArchivo_->addAction(actRecientes_);

    actSalir_ = new QAction(tr("&Salir"), this);
    actSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    mnuArchivo_->addAction(actSalir_);

    //HELP
    mnuHelp_ = new QMenu(tr("&Help"), this);
    mainMenu_->addMenu(mnuHelp_);

    actAbout_ = new QAction(tr("&About"), this);
    actAbout_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    mnuHelp_->addAction(actAbout_);

    //Ver
    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_->addMenu(mnuVer_);

    actfullscreen_ = new QAction(tr("&Pantalla Completa"), this);
    actfullscreen_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    mnuVer_->addAction(actfullscreen_);

    actmetadatos_ = new QAction(tr("&Metadatos"), this);
    mnuVer_->addAction(actmetadatos_);

    actstreaming_ = new QAction(tr("&Streaming"), this);
    mnuVer_->addAction(actstreaming_);

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

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64))); //cambia la duración cuando se hace un cambio de archivo, y por lo tanto le decimos que cambie su range el slider.
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(onOpen()));
    connect(actSalir_, SIGNAL(triggered()), this,  SLOT(onExit()));
    connect(actAbout_, SIGNAL(triggered()), this,  SLOT(onAbout()));
    connect(actfullscreen_, SIGNAL(triggered()), this,  SLOT(fullScreen()));
    connect(actmetadatos_, SIGNAL(triggered()), this,  SLOT(metadatos()));
    connect(actstreaming_, SIGNAL(triggered()), this,  SLOT(toStreaming()));

    url_example_ = "http://208.92.53.87:80/MAXIMAFM";

}

MainWindow::~MainWindow()
{

}

bool MainWindow::event(QEvent *evento)
{
    if (evento->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(evento);
        if (ke->key() == Qt::Key_Escape) {
            videoWidget_->setFullScreen(false);
            return true;
        }
    }
    return false;
}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    Recientes recientes;
    //QString culo;

    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        recientes.addReciente(fileName);
        //culo=fileName.section('/',-1,-1);
        //recientes.addReciente(culo);

    }
}

void MainWindow::onExit()
{
    QMessageBox sure;
    sure.setWindowTitle(tr("Aviso"));
    sure.setText(tr("¿Está seguro que desea salir?"));
    sure.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    int ret = sure.exec();

    if (ret == QMessageBox::Ok)
        close();
}

void MainWindow::onAbout()
{
    QMessageBox about;
    about.setWindowTitle(tr("About"));
    about.setText(tr("Reproductor -- de Haniel Martín"));
    about.addButton(tr("Cerrar"), QMessageBox::RejectRole);
    about.exec();
}

void MainWindow::fullScreen()
{
    if(!videoWidget_->isFullScreen()){
        videoWidget_->setFullScreen(true);
    }
    else{
        videoWidget_->setFullScreen(false);
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

void MainWindow::metadatos()
{
    QStringList ldatos= mediaPlayer_->availableMetaData();
    qDebug()<<mediaPlayer_->availableMetaData();

    if (ldatos.empty()) {
        QMessageBox::information(this, tr("Error"),tr("No puede ver los metadatos, porque este fichero no tiene metadatos."));
        return;
    }

    QDialog mensaje;
    QLayout* nuevo_layout = new QGridLayout(&mensaje);

    QLabel* Texto = new QLabel(ldatos.join("<br/>"), this);

    nuevo_layout->addWidget(Texto);

    mensaje.setLayout(nuevo_layout);
    mensaje.setWindowTitle("Metadatos");
    mensaje.setMinimumWidth(300);
    mensaje.exec();
}

void MainWindow::toStreaming()
{
    bool aceptar=false;

    QString url = QInputDialog::getText(this, tr("Streaming"),tr("Introduzca la URL:"),QLineEdit::Normal,url_example_,&aceptar);
    QRegExp whiteSpaces("^\\s+$");//limpiar lo posibles caracter no validos

    //aceptamos, hemos escrito algo y tenemos una url
    if (aceptar && !url.isEmpty() && !whiteSpaces.exactMatch(url)) {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(url));
        mediaPlayer_->play();
    }
}
