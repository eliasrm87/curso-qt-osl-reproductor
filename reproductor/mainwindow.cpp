#include "mainwindow.h"

#include <QListWidgetItem>
#include <QStringList>

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

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this); //Clase que se encarga la gestion de archivos multimedia
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);
    label_name    = new QLabel(this);
    videoWidget_->installEventFilter(this);

    //Configuracion del menu Archivo
    mainMenu_ = new QMenu(tr("&Archivo"),this);
    actAbrir_ = new QAction(tr("&Abrir"),this);
    actAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mainMenu_->addAction(actAbrir_);

    //Menu de archivos recientes
    mnuRecientes_ = new QMenu(tr("&Recientes"),this);
    mainMenu_->addMenu(mnuRecientes_);

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
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);
    lytMain_->addWidget(label_name,    2, 5, 1, 1);

    //Buttons icons
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    //Configuramos el menu de propiedades
    mnprop_ = new QMenu(tr("&Propiedades"),this);
    actConfig_ = new QAction(tr("&Configurar"),this);
    mnprop_->addAction(actConfig_);

    diag_prop_ = new QDialog(this);
    lyprop_ = new QGridLayout(diag_prop_);

    //Slider del brillo
    lbbrigth_ = new QLabel(tr("Brillo"),this);
    slibright_ = new QSlider(Qt::Horizontal, this);
    slibright_->setRange(0, 100);
    slibright_->setSliderPosition(50); //Brillo por defecto al 50%
    lyprop_->addWidget(lbbrigth_,   0,  0,  1,  1);
    lyprop_->addWidget(slibright_,  1,  0,  1,  1);

    //SLider de saturacion
    lbbsatur_ = new QLabel(tr("Saturación"),this);
    slisatur_ = new QSlider(Qt::Horizontal,this);
    slisatur_->setRange(0,100);
    slisatur_->setSliderPosition(50);
    lyprop_->addWidget(lbbsatur_,   2,  0,  1,  1);
    lyprop_->addWidget(slisatur_,   3,  0,  1,  1);

    //Slider de Contraste
    lbcontrst_ = new QLabel(tr("Contraste"),this);
    slcontrst_ = new QSlider(Qt::Horizontal,this);
    slcontrst_->setRange(0,100);
    slcontrst_->setSliderPosition(50);
    lyprop_->addWidget(lbcontrst_,    4,  0,  1,  1);
    lyprop_->addWidget(slcontrst_,    5,  0,  1,  1);

    //Configuracion del menu de LiveStream
    actLiveStream_ = new QAction(tr("&Livestreaming"),this);
    diag_LiveStream_ = new QDialog(this);
    lyLiveStream_ = new QGridLayout(diag_LiveStream_);
    lbLiveStream_ =  new QLabel(tr("URL"),this);
    lndtLiveStream_ = new QLineEdit(this);
    lyLiveStream_->addWidget(lbLiveStream_,   0,  0,  1,  1);
    lyLiveStream_->addWidget(lndtLiveStream_, 1,  0,  1,  1);
    mainMenu_->addAction(actLiveStream_);

    //Configuracion de la lista de reproduccion
    play_list = new QMediaPlaylist(this);
    mnPlay_list = new QMenu(tr("Lista de reproduccion"),this);
    rdn_play = new QAction(tr("&Random"),this);
    rdn_play->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    loop_play = new QAction(tr("Repetir"),this);
    loop_play->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    addplaylist_ = new QAction(tr("&Añadir a lista de reproduccion"),this);
    removeplaylist_ = new QAction(tr("&Eliminar de lista de reproduccion"),this);
    mnPlay_list->addAction(addplaylist_);
    mnPlay_list->addAction(removeplaylist_);
    mnPlay_list->addAction(rdn_play);
    mnPlay_list->addAction(loop_play);
    btnNext_ = new QAction(tr("&Siguiente"),this);
    btnNext_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    btnAfter_= new QAction(tr("&Anterior"),this);
    btnAfter_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    btnAfter_->setIcon(QIcon(QPixmap(":/icons/resources/after.png")));
    btnNext_->setIcon(QIcon(QPixmap(":/icons/resources/next.png")));
    mnPlay_list->addAction(btnAfter_);
    mnPlay_list->addAction(btnNext_);
    showPlaylist_ = new QAction(tr("&Mostrar lista de reproduccion"),this);
    showPlaylist_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnPlay_list->addAction(showPlaylist_);
    mainMenu_->addMenu(mnPlay_list);


    //Configuramos la barra de menu
    mnBar_->addMenu(mainMenu_);
    mnBar_->addMenu(mnVer_);
    mnBar_->addMenu(mnAyuda_);
    mnBar_->addMenu(mnprop_);
    this->setMenuBar(mnBar_);

    //Configuramos el QDialog del menu de ayuda
    dialog_acer = new QDialog(this);
    layout_acer = new QGridLayout(dialog_acer);
    label_1 = new QLabel(tr("Reproductor Multimedia Qt"),this);
    label_2 = new QLabel(this);
    label_2->setPixmap(QPixmap(":/icons/resources/winamp-logo-4.png"));

    layout_acer->addWidget(label_1,   0, 0, 1, 1);
    layout_acer->addWidget(label_2,   0, 1, 1, 1);



    //Connections
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));


    //Conexiones del menu
    connect(actAbrir_,      SIGNAL(triggered()),        this,       SLOT(onOpen()));
    connect(actConfig_,     SIGNAL(triggered()),        this,       SLOT(onPropiedades()));
    connect(slibright_,     SIGNAL(sliderReleased()),   this,       SLOT(onBrightChanged(qint64)));
    connect(slisatur_,      SIGNAL(sliderReleased()),   this,       SLOT(onSaturationChanged(qint64)));
    connect(slcontrst_,     SIGNAL(sliderReleased()),   this,       SLOT(onContrastChanged(qint64)));
    connect(actAyuda_,      SIGNAL(triggered()),        this,       SLOT(onHelp()));
    connect(actLiveStream_, SIGNAL(triggered()),        this,       SLOT(onLive()));
    connect(actFullscreen_, SIGNAL(triggered()),        this,       SLOT(onFullScreen()));
    connect(rdn_play,       SIGNAL(triggered()),        this,       SLOT(onRandom()));
    connect(loop_play,      SIGNAL(triggered()),        this,       SLOT(onLoop()));
    connect(addplaylist_,   SIGNAL(triggered()),        this,       SLOT(onAdd()));
    connect(removeplaylist_,SIGNAL(triggered()),        this,       SLOT(onRemove()));
    connect(btnAfter_,      SIGNAL(triggered()),        this,       SLOT(onNext()));
    connect(btnNext_,       SIGNAL(triggered()),        this,       SLOT(onAfter()));
    connect(showPlaylist_,  SIGNAL(triggered()),        this,       SLOT(onShowPlaylist()));

    connect(mediaPlayer_,   &QMediaPlayer::mediaChanged,    [&](){

        QString nuevo = mediaPlayer_->currentMedia().canonicalUrl().toEncoded();
        nuevo=nuevo.section("/",-1);
        label_name->setText(nuevo);

    });
}

void MainWindow :: onShowPlaylist(){

    QDialog dialogo;
    QGridLayout* ly = new QGridLayout(&dialogo);
    QListWidget list;
    QLabel lb("Lista de Reproduccion Actual");
    int i=0;
    QList<QString> contenido;

    while(i < play_list->mediaCount()){

    QString nuevo = play_list->media(i).canonicalUrl().toEncoded();
    nuevo=nuevo.section("/",-1);
    contenido.push_back(nuevo);
    i++;
    }

    list.addItems(contenido);
    ly->addWidget(&lb,    0,  0,  1,  1);
    ly->addWidget(&list,  1,  0,  1,  1);
    dialogo.exec();


}

void MainWindow :: onAfter(){

    if(!play_list->isEmpty()){
      play_list->setCurrentIndex(play_list->previousIndex());
        mediaPlayer_->play();
    }

}

void MainWindow :: onNext(){

    if(!play_list->isEmpty()){
    play_list->setCurrentIndex(play_list->nextIndex());
    mediaPlayer_->play();
    }
}

//Añadimos un elemento a la lista de reproduccion
void MainWindow :: onAdd(){

    if (!mediaPlayer_->state() == QMediaPlayer::StoppedState) //Si estamos reproduciendo añadimos lo que tenemos
        play_list->addMedia(mediaPlayer_->currentMedia());

    mediaPlayer_->setPlaylist(play_list);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Añadir Archivo"));

    if (fileName != "") {
        play_list->addMedia(QUrl::fromLocalFile(fileName));
        this->addRecent(fileName);
        this->onRecent();
        }


        mediaPlayer_->play();

}

//Eliminamos el elemento actual
void MainWindow :: onRemove(){

    mediaPlayer_->stop();
    int pos = play_list->nextIndex(); //Siguiente elemento a reproducir
    play_list->removeMedia(play_list->currentIndex());
    play_list->setCurrentIndex(pos);
    mediaPlayer_->play();

}

void MainWindow :: onRandom(){

    if (play_list->playbackMode() == QMediaPlaylist::Random)
        play_list->setPlaybackMode(QMediaPlaylist::Sequential);

    else if (play_list->playbackMode() == QMediaPlaylist::Sequential)
       play_list->setPlaybackMode(QMediaPlaylist::Random);

}

void MainWindow :: onLoop(){

    if (play_list->playbackMode() == QMediaPlaylist::Loop)
        play_list->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    else if (play_list->playbackMode() == QMediaPlaylist::CurrentItemOnce)
       play_list->setPlaybackMode(QMediaPlaylist::Loop);

}


void MainWindow :: start_playlist(){

   if( !play_list->isEmpty() ){ //Si no esta vacia se la asignamos al reproductor

    play_list->setCurrentIndex(1);
    mediaPlayer_->setPlaylist(play_list);
    mediaPlayer_->play();
   }
}

void MainWindow :: addToPlaylist(QString media){

    if (media != "")
     play_list->addMedia(QUrl::fromLocalFile(media));

}

void MainWindow :: removeFromPlaylist(){

    play_list->removeMedia(play_list->currentIndex());
}



//SLOT PARA LIVESTREAM
void MainWindow :: onLive(){

    diag_LiveStream_->showNormal();

    connect (lndtLiveStream_, &QLineEdit::returnPressed, [&](){

    if (lndtLiveStream_->text() != ""){
      diag_LiveStream_->close();
      mediaPlayer_->setMedia(QUrl(lndtLiveStream_->text()));
      mediaPlayer_->play();
    }

    });

}


void MainWindow :: onFullScreen(){

    if (!videoWidget_->isFullScreen())
        videoWidget_->setFullScreen(true);

    else
        videoWidget_->setFullScreen(false);
}

//Mostramos el dialogo para configurar la imagen
void MainWindow :: onPropiedades(){

    diag_prop_->showNormal();

}

//SLOTS PARA MODIFICAR LAS PROPIEDADES DE LA IMAGEN
void MainWindow :: onBrightChanged(qint64 brillo){

    slibright_->setSliderPosition(brillo);
    videoWidget_->setBrightness(brillo);

}

void MainWindow :: onContrastChanged(qint64 contraste){

    slcontrst_->setSliderPosition(contraste);
    videoWidget_->setContrast(contraste);
}

void MainWindow :: onSaturationChanged(qint64 saturacion){

    slisatur_->setSliderPosition(saturacion);
    videoWidget_->setSaturation(saturacion);
}


//MOSTRAMOS EL DIALOGO DE AYUDA
void MainWindow :: onHelp(){

    dialog_acer->showNormal();
}


//ABRIMOS LOS ARCHIVOS RECIENTES
void MainWindow::onRecent()
{
    QFile recientes("../recientes.txt");
    if (recientes.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Eliminamos las acciones (path) del menú si ya se habían añadido
        mnuRecientes_->clear();

        // Obtenemos las reproducciones recientes
        QTextStream in(&recientes);
        while (!in.atEnd()) {
            QString archivo = in.readLine();
            QAction *actAbrirArchivo = new QAction(archivo, this);
            mnuRecientes_->addAction(actAbrirArchivo);
            connect(actAbrirArchivo, SIGNAL(triggered()), this, SLOT(opRecent()));
        }

        // Si hay acciones recientes, damos opción de borrado
        if (recientes.size() != 0) {
            mnuRecientes_->addSeparator();
            actArchivoBorrarRecientes_ = new QAction(tr("Borrar historial de recientes"), this);
            mnuRecientes_->addAction(actArchivoBorrarRecientes_);
            connect(actArchivoBorrarRecientes_, SIGNAL(triggered()), this, SLOT(remRecent()));
        }
        recientes.close();
    }
}

void MainWindow::addRecent(QString archivo)
{
    QFile recientes("../recientes.txt");
    if (recientes.open(QIODevice::Append)) {
        QTextStream out(&recientes);
        out << archivo << endl;
        recientes.close();
    }
}

void MainWindow::opRecent()
{
    QAction *accion = (QAction*)QObject::sender();
    mediaPlayer_->setMedia(QUrl::fromLocalFile(accion->text()));
    mediaPlayer_->play();
}

void MainWindow::remRecent()
{
    // Vaciamos el fichero de recientes
    QFile recientes("../recientes.txt");
    if (recientes.open(QIODevice::Append | QIODevice::Text)) {
        recientes.resize(0);
        recientes.close();

        // Eliminamos las acciones (path) del menú
        mnuRecientes_->clear();
    }

    // Refrescamos la barra
    this->onRecent();
}


//ABRIMOS UN NUEVO ARCHIVO
void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir archivo"));

    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        this->addRecent(fileName);
        this->onRecent();
        fileName=fileName.section("/",-1);
        label_name->setText(fileName);
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
    playerSlider_->setSliderPosition(position); //Cambiamos el punto de reproduccion
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouse = static_cast<QMouseEvent *>(event);

    if (obj == videoWidget_) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            if(mouse->button() == Qt::LeftButton){
                if(!videoWidget_->isFullScreen()){
                    videoWidget_->setFullScreen(true);
                }
                else{
                    videoWidget_->setFullScreen(false);
                }
                return true;
            }
        }
        else{
            return false;
        }
    }
    return false;
}

MainWindow :: ~MainWindow(){

   lytMain_->deleteLater();
   wgtMain_->deleteLater();
   mediaPlayer_->deleteLater();
   playerSlider_->deleteLater();
   videoWidget_->deleteLater();
   volumeSlider_->deleteLater();
   btnPlay_->deleteLater();
   btnPause_->deleteLater();
   btnStop_->deleteLater();

   label_name->deleteLater();
   mnBar_->deleteLater();
   mainMenu_->deleteLater();
   actAbrir_->deleteLater();
   mnuRecientes_->deleteLater();
   mnAyuda_->deleteLater();
   actAyuda_->deleteLater();
   mnVer_->deleteLater();
   actFullscreen_->deleteLater();
   actMetadatos_->deleteLater();
   dialog_acer->deleteLater();
   label_1->deleteLater();
   label_2->deleteLater();
   layout_acer->deleteLater();



}
