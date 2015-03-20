#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    actArchivoAbrir_=new QAction(tr("&Abrir"),this);



    mainmenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainmenu_->addMenu(mnuArchivo_);

    mnuVer_= new QMenu(tr("&Ver"), this);
    mainmenu_->addMenu(mnuVer_);

    mnuAyuda_= new QMenu(tr("&Ayuda"), this);
    mainmenu_-> addMenu(mnuAyuda_);

    actArchivoSalir_= new QAction(tr("&Salir"), this);
    actVerpc_= new QAction(tr("&Pantalla Completa"), this);
    actVerMetadatos_= new QAction(tr("&Metadatos"), this);
    actArchivosRecientes_= new QMenu(tr("&Recientes"), this);
    actAcercade_= new QAction(tr("&Acerca de"), this);
    actminimizar_= new QAction(tr("Salir pantalla completa"),this);
    minimizar_= new QAction(tr("Minimizar"),this);

    mnuArchivo_->addAction(actArchivoSalir_);
    mnuVer_->addAction(actVerpc_);
    mnuArchivo_->addMenu(actArchivosRecientes_);
    mnuVer_->addAction(actVerMetadatos_);
    mnuAyuda_->addAction(actAcercade_);
    mnuArchivo_->addAction(actArchivoAbrir_);
    mnuArchivo_->addAction(actminimizar_);

    actminimizar_->setShortcut(QKeySequence(Qt::Key_Escape));
    actVerpc_->setShortcut(QKeySequence(Qt::Key_F11));
    this->setMenuBar(mainmenu_);




    mnuArchivo_->addMenu(actArchivosRecientes_);
    toolbar_= new QToolBar(this);
    this->addToolBar(toolbar_);
    mnuVer_->addAction(minimizar_);

    toolbar_->addAction(actArchivoSalir_);
    actArchivoSalir_->setIcon(QIcon(QPixmap(":/icons/resources/PublicInformationSymbol_EmergencyExit.png")));

    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    recientes();//archivos recientes


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
    videoWidget_->setMinimumSize(600, 400);
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
    actArchivoSalir_->setIcon(QIcon(QPixmap(":/icons/resources/PublicInformationSymbol_EmergencyExit.png")));

    //Connections
    connect(btnOpen_,         SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,         SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,        SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,         SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_,    SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,     SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,     SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_,    SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(actArchivoSalir_, SIGNAL(triggered()),             this,         SLOT(alSalir()));
    connect(actVerpc_,        SIGNAL(triggered()),             this,         SLOT(pc()));
    connect(actminimizar_,    SIGNAL(triggered()),             this,         SLOT(es()));
    connect(actArchivoAbrir_, SIGNAL(triggered()),             this,         SLOT(onOpen()));
    connect(actAcercade_,     SIGNAL(triggered()),             this,         SLOT(dialog()));
    connect(minimizar_,       SIGNAL(triggered()),             this,         SLOT(minimizar()));
    connect(actVerMetadatos_, SIGNAL(triggered()),             this,         SLOT(metadatos()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::recientes(){
    QFile file("Recientes.txt");
    QAction* recientes;
    QTextStream textStream(&file);
    file.open(QIODevice::ReadOnly);

    while(!textStream.atEnd()){
       line = textStream.readLine();
       recientes= new QAction(line,this);
       actArchivosRecientes_->addAction(recientes);
       connect(recientes, SIGNAL(triggered()),  this,  SLOT(onOpenrecientes()));
       }
    file.close();
}

void MainWindow::onOpen(){
        //Show file open dialog
        QString fileName = QFileDialog::getOpenFileName(this,   tr("Abrir archivo"));
        QFile file("Recientes.txt");
        file.open(QIODevice::ReadWrite|QIODevice::Append);
        QTextStream out(&file);
        out << fileName << endl;
        file.close();
        if (fileName != "") {
            mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        }
}

void MainWindow::onOpenrecientes(){                         //intento de lanzar el archivo
        if (line != "") {
           mediaPlayer_->setMedia(QUrl::fromLocalFile(line));
        }

}
void MainWindow::metadatos()
{
}


void MainWindow::es()
{
    this->setWindowState(Qt::WindowNoState);
}

void MainWindow::minimizar()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::pc()
{
this->setWindowState(Qt::WindowFullScreen);}

void MainWindow::dialog()
{
    QDialog dialogo;
    dialogo.setWindowTitle("Acerca de");
    dialogo.exec();
}


void MainWindow::alSalir()
{
    this->close();
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
