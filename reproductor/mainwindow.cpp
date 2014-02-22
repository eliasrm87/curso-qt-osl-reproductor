#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout //Centra ventana
    wgtMain_ = new QWidget(this);//Estam la ventana principal
    lytMain_ = new QGridLayout(wgtMain_);//Permite dividir el espacio y añadir elementos (ver matriz)
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);//Indicamos si es vertical u horizontal
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);//Cuadro negro definimos el tamaño para verlo
    mediaPlayer_->setVideoOutput(videoWidget_);//Objeto de decodificacion del video
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);//Redimensionar se establezca
    volumeSlider_->setRange(0, 100);//El volumen
    volumeSlider_->setSliderPosition(100);//Colocacion del slider

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 5);//Coordenadas (ultimo fila y columna te espandes)
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

    //Menu
    mainMenu_= new QMenuBar(this);

    //Archivo
    mnuArchivo_ = new QMenu (tr("&Archivo"), this);//Especificamos el texto del menu
    mainMenu_-> addMenu(mnuArchivo_);

    mnuArchivoRecientes_ = new QMenu (tr("&Recientes"), this);
    mnuArchivo_-> addMenu(mnuArchivoRecientes_);

    //abrir
    actArchivoAbrir_ = new QAction(QIcon(":/icons/resources/eject.png"),tr("&Abrir"),this);
    actArchivoAbrir_-> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));

    //Ver
    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_-> addMenu(mnuVer_);

    //PantallaCompleta
    actVerCompleta_= new QAction (tr("&Pantalla Completa"),this);
    actVerCompleta_-> setShortcut(QKeySequence(Qt::ALT + Qt::Key_F));

    //Metadatos
    actMetadatos_=new QAction(tr("&Metadados"),this);



    //Ayuda
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    //Acercade
    actAyudaAcerca_=new QAction(tr("&Acerca de"), this);


    //add acciones
    mnuArchivo_->addAction(actArchivoAbrir_);

    mnuAyuda_->addAction(actAyudaAcerca_);
    mnuVer_->addAction(actVerCompleta_);
    mnuVer_->addAction(actMetadatos_);


    //Colocacion de elementos
    //le decimos donde colocarse la barra del menu y la de herramientas
    setMenuBar(mainMenu_);



    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(actArchivoAbrir_, SIGNAL(triggered()),this, SLOT (onOpen()));
    connect(actAyudaAcerca_, SIGNAL(triggered()), this, SLOT (acerca()));
    connect(actVerCompleta_,SIGNAL(triggered()),this,SLOT (pantallaCompleta()));
    connect(actMetadatos_,SIGNAL(triggered()),this,SLOT(metadatos()));
}


MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //Para reproductir en streaming
    //falta poner un cuadro de dialogo para introducir la dire:
    //Guardamos como el metaDatos justo despues del exe.
    // mediaPlayer_->setMedia(QUrl("http://288.92.53.87:80/MAXIMAFM"));//online radio

    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abrir archivo"));
    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        fileOpen_ = QUrl::fromLocalFile(fileName).toString();
        guardarReciente(fileOpen_);
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
    QMessageBox::about(this,"Acerca de","Este es un reproductor de videos con falta de codecs");
}

void MainWindow::pantallaCompleta()
{
    if (videoWidget_->isFullScreen()){
        videoWidget_->setFullScreen(false);

    }else
        videoWidget_->setFullScreen(true);

}

void MainWindow::verRecientes()
{


}

void MainWindow::guardarReciente(QString linea)
{
    QFile file("recientes.txt");
    file.open(QIODevice::Append);

    QTextStream out(&file);

    out << linea << endl;//Escribimos
    actArchivoRecientes_= new QAction(linea,this);
    mnuArchivoRecientes_->addAction(actArchivoRecientes_);
    connect(actArchivoRecientes_,SIGNAL(triggered()),this,SLOT(pulsarRecientes()));

    file.close();
}

void MainWindow::metadatos()
{
    MetaDataDialog md (mediaPlayer_,this);
    md.exec();

}

void MainWindow::pulsarRecientes()
{
    QAction* act = (QAction*)QObject::sender();//Puntero al objeto que envio la señal que activo este slot
    mediaPlayer_->setMedia(QUrl(act->text()));
}


