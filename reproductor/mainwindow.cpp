#include "mainwindow.h"
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("Reproductor Multimedia Qt");
    this->setWindowIcon(QPixmap(":/icons/resources/winamp-logo-4.png"));

    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);
    mnBar_ = new QMenuBar(this);
    fich_recent = new QFile("Fichero recientes.txt");


    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this); //Clase que se encarga la gestion de archivos multimedia
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);
    label_name    = new QLabel(this);
    play_list     = new QListWidget(this);

    //Configuracion del menu Archivo
    mainMenu_ = new QMenu(tr("&Archivo"),this);
    actAbrir_ = new QAction(tr("&Abrir"),this);
    actAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actRecientes_ = new QAction(tr("&Recientes"),this);
    actRecientes_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    live_stream = new QAction(tr("&Streaming"),this);
    live_diag = new QDialog(this);
    ly_livestream = new QGridLayout(live_diag);
    live_lb.setText(tr("URL: "));
    ly_livestream->addWidget(&live_lb,       0,  0,  1,  1);
    ly_livestream->addWidget(&live_lnedit,   1,  1,  1,  1);

    mainMenu_->addAction(actAbrir_);
    mainMenu_->addAction(actRecientes_);
    mainMenu_->addAction(live_stream);




    //Configuracion del menu Ver
    mnVer_ = new QMenu(tr("&Ver"),this);
    actFullscreen_ = new QAction(tr("&Pantalla Completa"),this);
    actFullscreen_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    actMetadatos_ = new QAction(tr("&Metadatos"),this);
    actMetadatos_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnVer_->addAction(actFullscreen_);
    mnVer_->addAction(actMetadatos_);

    //Configuracion del menu Ayuda
    mnAyuda_ = new QMenu(tr("&Ayuda"),this);
    actAyuda_ = new QAction(tr("&Acerca de "),this);
    actAyuda_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    mnAyuda_->addAction(actAyuda_);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400); //Tamaño de la pantalla de video
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(50); //Volumen al maximo por defecto

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 5);
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 5);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);
    lytMain_->addWidget(label_name,    2, 5, 1, 1);
    lytMain_->addWidget(play_list,     0, 5, 1, 1);

    //Buttons icons
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

//    //Configuramos el menu de propiedades
//    mnprop_ = new QMenu(tr("&Propiedades"),this);
//    actConfig_ = new QAction(tr("&Configurar"),this);
//    mnprop_->addAction(actConfig_);

//    diag_prop_ = new QDialog(this);
//    lyprop_ = new QGridLayout(diag_prop_);

//    //Slider del brillo
//    lbbrigth_ = new QLabel(tr("&Brillo"),this);
//    slibright_ = new QSlider(Qt::Horizontal, this);
//    slibright_->setRange(0, 100);
//    slibright_->setSliderPosition(50); //Brillo por defecto al 50%
//    lyprop_->addWidget(lbbrigth_,   0,  0,  1,  1);
//    lyprop_->addWidget(slibright_,  1,  0,  1,  1);

//    //SLider de saturacion
//    lbbsatur_ = new QLabel(tr("&Saturación"),this);
//    slisatur_ = new QSlider(Qt::Horizontal,this);
//    slisatur_->setRange(0,100);
//    slisatur_->setSliderPosition(50);
//    lyprop_->addWidget(lbbsatur_,   2,  0,  1,  1);
//    lyprop_->addWidget(slisatur_,   3,  0,  1,  1);

//    //Slider de Contraste
//    lbcontrst_ = new QLabel(tr("&Contraste"),this);
//    slcontrst_ = new QSlider(Qt::Horizontal,this);
//    slcontrst_->setRange(0,100);
//    slcontrst_->setSliderPosition(50);
//    lyprop_->addWidget(lbcontrst_,    4,  0,  1,  1);
//    lyprop_->addWidget(slcontrst_,    5,  0,  1,  1);

    //Configuramos la barra de menu
    mnBar_->addMenu(mainMenu_);
    mnBar_->addMenu(mnVer_);
    mnBar_->addMenu(mnAyuda_);
  //  mnBar_->addMenu(mnprop_);
    setMenuBar(mnBar_);

    //Connections
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(play_list,     SIGNAL(itemSelectionChanged()),  this,         SLOT(onSelect()));
    connect(live_stream,   SIGNAL(triggered()),             this,         SLOT(onLive()));


    //Conexiones del menu
    connect(actAbrir_,      SIGNAL(triggered()),     this,       SLOT(onOpen()));
    connect(actRecientes_,  SIGNAL(triggered()),     this,       SLOT(onRecent()));
//    connect(actConfig_,     SIGNAL(triggered()),     this,       SLOT(onPropiedades()));
//    connect(slibright_,     SIGNAL(sliderReleased()), this,      SLOT(onBrightChanged(qint64)));
//    connect(slisatur_,      SIGNAL(sliderReleased()), this,      SLOT(onSaturationChanged(qint64)));
//    connect(slcontrst_,     SIGNAL(sliderReleased()), this,      SLOT(onContrastChanged(qint64)));


    //Configuramos el QDialog del menu de ayuda
    dialog_acer = new QDialog(this);
    layout_acer = new QGridLayout(dialog_acer);
    label_1 = new QLabel(tr("Reproductor Multimedia Qt"),this);
    label_2 = new QLabel(this);
    label_2->setPixmap(QPixmap(":/icons/resources/winamp-logo-4.png"));

    layout_acer->addWidget(label_1,   0, 0, 1, 1);
    layout_acer->addWidget(label_2,   0, 1, 1, 1);
    //Realizamos la conexion
    connect(actAyuda_,      SIGNAL(triggered()),    this,       SLOT(onHelp()));
}

////Mostramos el dialogo para configurar la imagen
//void MainWindow :: onPropiedades(){

//    diag_prop_->showNormal();

//}

////SLOTS PARA MODIFICAR LAS PROPIEDADES DE LA IMAGEN
//void MainWindow :: onBrightChanged(qint64 brillo){

//    slibright_->setSliderPosition(brillo);
//}

//void MainWindow :: onContrastChanged(qint64 contraste){

//    slcontrst_->setSliderPosition(contraste);
//}

//void MainWindow :: onSaturationChanged(qint64 saturacion){

//    slisatur_->setSliderPosition(saturacion);
//}


void MainWindow :: onLive(){

    live_diag->show();

    /*connect(live_lnedit, &QLineEdit::returnPressed, [&](){

     if(live_lnedit->text() != ""){
         QString url = live_lnedit->text();
         mediaPlayer_->setMedia(QUrl(url));
         mediaPlayer_->play();

     }

    });*/


}

//MOSTRAMOS EL DIALOGO DE AYUDA
void MainWindow :: onHelp(){

    dialog_acer->showNormal();
}

MainWindow::~MainWindow(){}


//ABRIMOS LOS ARCHIVOS RECIENTES
void MainWindow :: onRecent(){

    if(fich_recent->open(QFile::ReadOnly | QFile::Text)){
     QTextStream text(fich_recent);
     QString item;

     while (!fich_recent->atEnd()){
      item = fich_recent->readLine();
      play_list->addItem(item);

     }

     fich_recent->close();
    }


}

//ABRIMOS UN NUEVO ARCHIVO
void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir archivo"));

    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        play_list->clear();
        play_list->addItem(fileName);


        if(fich_recent->open(QFile::ReadWrite | QFile::Append | QFile::Text)){

        QTextStream text (fich_recent);
        QString existe;
        existe = fich_recent->readAll();

        if(!existe.contains(fileName))
          text << fileName << endl;

        fich_recent->close();

        }

        fileName=fileName.section("/",-1);
        label_name->setText(fileName);

    }
}

//CAMBIAMOS EL ARCHIVO A REPRODUCIR
void MainWindow::onSelect(){


    QListWidgetItem* item = play_list->item(play_list->currentRow());
    QString name = item->text();
    mediaPlayer_->setMedia(QUrl::fromLocalFile(name));
    name= name.section("/",-1);
    label_name->setText(name);
    mediaPlayer_->play();


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
    playerSlider_->setSliderPosition(position); //Cambiamos el punto de reproduccion
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}
