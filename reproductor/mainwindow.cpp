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
    //volumeSlider_ = new QSlider(Qt::Horizontal, this);
    volumeSlider_ = new QSlider(Qt::Vertical,this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    btnMinimizar_ = new QToolButton(this);
    //botones nuevos para las tareas
    btnAleatoria_ = new QToolButton(this);
    btnBucle_ = new QToolButton(this);


    //Sliders para el brillo, contraste y saturación
    brightnessSlider_ = new QSlider(Qt::Vertical);
    contrastSlider_ =   new QSlider(Qt::Vertical);
    saturavionSlider_ = new QSlider(Qt::Vertical);


    //Setup widwgets
    videoWidget_->setMinimumSize(600, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(50);
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

    lytMain_->addWidget(btnMinimizar_, 0, 5, 1, 1);

    //botones nuevos
    lytMain_->addWidget(btnAleatoria_, 2,4,1,1);
    lytMain_->addWidget(btnBucle_, 2,5,1,1);


    lytMain_->addWidget(volumeSlider_, 2, 6, 1, 1);


    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    btnMinimizar_->setIcon(QIcon(QPixmap(":/icons/resources/minimizar.png")));

    //Buttons nuevos tareas icons
    btnAleatoria_->setIcon(QIcon(QPixmap(":/icons/resources/aleatoria.jpg")));
    btnBucle_->setIcon(QIcon(QPixmap(":/icons/resources/repetir.jpg")));

    //menu principal
    main_menu_= new QMenuBar(this);

    menu_archivo_= new QMenu ("Archivo", this);
    main_menu_->addMenu(menu_archivo_);
    setMenuBar(main_menu_);


    menu_ver_ = new QMenu ("Ver", this);
    main_menu_->addMenu(menu_ver_);
    setMenuBar(main_menu_);


    //Abrir
    Abrir_ = new QAction("Abrir", this);
    menu_archivo_->addAction(Abrir_);

    //Recientes
    Recientes_ = new QAction("Reciente", this);
    menu_archivo_->addAction(Recientes_);
    lista_recientes_ = new QListWidget();

    Cerrar_Recientes_ = new QAction("Cerrar Recientes", this);

    //rrecientes_ = new QMenu(tr("Recientes"),this);
    //rrecientes_->addAction(Recientes_);
    //menu_archivo_->addMenu(rrecientes_);
    menu_archivo_->addAction(Cerrar_Recientes_);

    Cargar_Lista_Reproduccion_ = new QAction("Cargar Lista",this);
    menu_archivo_->addAction(Cargar_Lista_Reproduccion_);


    this->setWindowIcon(QIcon(QPixmap(":/icons/resources/repro.png")));


    playlist_ = new QMediaPlaylist();


    //Ayuda
    Ayuda_ = new QAction("Ayuda", this);
    menu_archivo_->addAction(Ayuda_);


    menu_editar_ = new QMenu("Editar", this);
    main_menu_->addMenu(menu_editar_);
    Editar_ = new QAction("Imagen", this);

    menu_editar_->addAction(Editar_);


    //Ver pantalla completa
    Ver_pantalla_completa_ = new QAction("Ver_completa", this);
    Metadatas_ = new QAction("Metadata", this);
    menu_ver_->addAction(Ver_pantalla_completa_);
    menu_ver_->addAction(Metadatas_);

   // pantalla_completa_deshacer_ = new QAction(this);
   // pantalla_completa_deshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));



    //salir de marcha
    Salir_ = new QAction("Salir", this);
    menu_archivo_->addAction(Salir_);



    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    //Connections NEW BUTTONS
    connect(btnBucle_,      SIGNAL(pressed()),              this,         SLOT(Bucle()));
    connect(btnAleatoria_,  SIGNAL(pressed()),              this,         SLOT(Aleatoria()));

    //boton minimizado
    connect(btnMinimizar_, SIGNAL(pressed()),              this,         SLOT(Minimizar()));

    //SLIDERS CONTRASTE SATURACION y BRILLO
    connect(contrastSlider_,      SIGNAL(sliderMoved(int)),               videoWidget_,         SLOT(setContrast(int)));
    connect(saturavionSlider_,      SIGNAL(sliderMoved(int)),               videoWidget_,         SLOT(setSaturation(int)));
    connect(brightnessSlider_,      SIGNAL(sliderMoved(int)),               videoWidget_,         SLOT(setBrightness(int)));


    connect(Editar_, SIGNAL(triggered()), this, SLOT(Ver_controles_edicion()) );

    //menu archivo
    connect(Abrir_, SIGNAL(triggered()), this, SLOT(Abrir()));

    connect(Recientes_, SIGNAL(triggered()), this, SLOT(Recientes_leer()));
    connect(Cerrar_Recientes_, SIGNAL(triggered()), this, SLOT(Cerrar_Recientes()));

    connect(Cargar_Lista_Reproduccion_,SIGNAL(triggered()), this, SLOT(Cargar_lista_reproduccion()));


    connect(Salir_, SIGNAL(triggered()), this, SLOT(Salir()));

    //menu ver pantalla completa
    connect(Ver_pantalla_completa_, SIGNAL(triggered()), this, SLOT(Pantalla_completa()));
    //connect(pantalla_completa_deshacer_, SIGNAL(pressed()), this, SLOT(Deshacer_pantalla_completa()));

    //METADATA
    connect(Metadatas_, SIGNAL(triggered()), this, SLOT(Ver_metadatos()));




}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //Show file open dialog
   // QString fileName = QFileDialog::getOpenFileName(this,
     //                                       tr("Abrir archivo"));
//    if (fileName != "") {
//        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
//        Recientes_crear(fileName);
//    }

    mediaPlayer_->setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM"));


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


void MainWindow::Aleatoria(){

    //if (playlist_->playbackMode() != QMediaPlaylist::Random){
     mediaPlayer_->stop();
     playlist_->setPlaybackMode(QMediaPlaylist::Random);
     mediaPlayer_->setPlaylist(playlist_);
     mediaPlayer_->play();
    //}
    //else{
    // playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
    // mediaPlayer_->setPlaylist(playlist_);
    //}


}


void MainWindow::Bucle(){

   if (playlist_->playbackMode() != QMediaPlaylist::Loop){
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);
    mediaPlayer_->setPlaylist(playlist_);
    mediaPlayer_->play();
   }
   else{
    mediaPlayer_->stop();
    playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
    mediaPlayer_->setPlaylist(playlist_);
    mediaPlayer_->play();
   }


}

void MainWindow::Cargar_lista_reproduccion(){

    inputDialog_ = new QInputDialog();
    bool ok;
    inputDialog_->setOptions(QInputDialog::NoButtons);

    QString dir = "http://";

    QString text = inputDialog_->getText(NULL, "Listas de Rerprodución M3U y/o PLS",
                                         "Introduzca la dirección:",
                                         QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    if (ok && !text.isEmpty()){



       lista_ = QMediaContent(QUrl(dir+text));

       playlist_->addMedia(lista_);
       mediaPlayer_->setPlaylist(playlist_);
       mediaPlayer_->play();

//        QTextStream cout(stdout,QIODevice::WriteOnly);
//        cout << dire.toString();



      //somafm.com/m3u/groovesalad.m3u

       //cope.stream.flumotion.com/cope/cadena100.mp3.m3u
       //rtve.stream.flumotion.com/rtve/radio3.mp3.m3u


    }




   // QString text = inputDialog


}


void MainWindow::Minimizar(){

    //this->setWindowFlags(windowFlags() | Qt::Tool);



    this->showMinimized();
    
    
}



//metodos del menu archivo
void MainWindow::Abrir(){

    //QString nombreArchivo;
    nombreArchivo_ = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de video"),
                                                 "",
                                                 tr("Archivo de video (*.mpeg *.avi *.wmv *.mp4 *.mov *.flv *.mp3 *.mpg)")
                                                 );
    if (nombreArchivo_ != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo_);
        if (archivo.open(QFile::ReadOnly)) {

            mediaPlayer_->setMedia(QUrl::fromLocalFile(nombreArchivo_));

            mediaPlayer_->play();
            //mediaPlayer_->setVideoOutput(videoWidget_);


            playlist_->addMedia(QUrl::fromLocalFile(nombreArchivo_));


            archivo.close();

            Recientes_crear(nombreArchivo_);

        }



    }




}

//Recientes
void MainWindow::Recientes_crear(QString nombreArchivo){

    QFile archivo;
    archivo.setFileName(nombre);
    if (archivo.open(QFile::WriteOnly | QFile::Append)) {
        archivo.write(nombreArchivo.toUtf8());
        archivo.write("\n");
        //Se cierra el fichero
        archivo.close();
        }

}





void MainWindow::Recientes_leer(){


    lista_recientes_->clear();
    lista_recientes_->setVisible(true);


    QFile archivo(nombre);

    if (archivo.open(QFile::ReadOnly | QIODevice::Text)) {
  //      archivo.read(nombreArchivo.toUtf8());

        QTextStream in(&archivo);

        while (!in.atEnd()) {
            QString Line = in.readLine();

            //QTextStream cout(stdout,QIODevice::WriteOnly);
            //cout << Line;

           // rrecientes_->setTitle(Line);

            lista_recientes_->addItem(new QListWidgetItem(Line));

            //rrecientes_->addMenu(Line);
            //QAction *Rec_ = new QAction("Rec", rrecientes_);


            //connect(lista_marcadores_, SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(cargarpagina(QListWidgetItem *)));

           // connect(Rec_, SIGNAL(pressed()) ,this ,SLOT(Play_recientes()));
            connect(lista_recientes_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(Play_recientes(QListWidgetItem *)));

        }



        archivo.close();
        }

}

void MainWindow::Play_recientes(QListWidgetItem *item){

    mediaPlayer_->setMedia(QUrl::fromLocalFile(item->text()));
    mediaPlayer_->play();

}

void MainWindow::Cerrar_Recientes (){

        lista_recientes_->setVisible(false);
}




//opciones del menu ver
void MainWindow::Pantalla_completa(){

    videoWidget_->setFullScreen(true);
    mediaPlayer_->setVideoOutput(videoWidget_);


}


void MainWindow::Deshacer_pantalla_completa(){

    videoWidget_->setFullScreen(false);
    mediaPlayer_->setVideoOutput(videoWidget_);

}


void MainWindow::Ver_metadatos(){

    MetadataDialog md(mediaPlayer_,this);
    md.exec();

}

void MainWindow::Ver_controles_edicion(){

    QWidget* controles = new QWidget;
    QGridLayout* layout_controles = new QGridLayout(controles);

    QLabel* brillo = new QLabel("BRILLO");
    QLabel* saturacion = new QLabel("SATURACION");
    QLabel* contraste = new QLabel("CONTRASTE");

    brillo->setAlignment(Qt::AlignLeft);
    saturacion->setAlignment(Qt::AlignCenter);
    contraste->setAlignment(Qt::AlignRight);

    layout_controles->addWidget(brightnessSlider_,2,0,1,1);
    layout_controles->addWidget(saturavionSlider_,2,1,1,1);
    layout_controles->addWidget(contrastSlider_,2,2,1,1);

    layout_controles->addWidget(brillo);
    layout_controles->addWidget(saturacion);
    layout_controles->addWidget(contraste);

    controles->setLayout(layout_controles);

    controles->setWindowTitle("CONTROLES DE VIDEO");
    controles->show();

}


void MainWindow::Ayuda(){
    //QString mensaje =

}


void MainWindow::Salir(){

    QMessageBox msg;
    msg.move(200,200);

    msg.setText("DESEA SALIR REALMENTE?");
    msg.addButton("SI", QMessageBox::YesRole);
    msg.addButton("NO", QMessageBox::NoRole);

    if (!msg.exec()){
        lista_recientes_->clear();
        QFile archivo(nombre);
        archivo.open(QFile::WriteOnly|QFile::Truncate);
        close();
    }
}
