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

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_); //Se establece cuál será el output del mediaplayer
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio); //mantener el ratio del video (16:9, 4:3,...)
    volumeSlider_->setRange(0, 100); //valor mínimo y máximo del sonido.
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    //Se colocan los widgets dentro del layout (fila, columna, filas que ocupa, columnas que ocupa)
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


    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    //Coloca la barra de menú correctamente.
    setMenuBar(mainMenu_);

    //----ARCHIVO----------
    //La primera opción se llamará "Archivo",
    // y se accederá a ella pulsando Alt + r, porque hemos colocado el & delante de la "r".
    //La función tr traduce desde archivos .po donde hemos establecido los diccionarios.
    //Es decir, la cadena "Archivo" podría ser traducida por "File".
    mnuArchivo_ = new QMenu(tr("A&rchivo"), this);
    //Se añade la opción Archivo a la barra de menú.
    mainMenu_->addMenu(mnuArchivo_);
    //Se inicializa la acción Abrir.
    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    //Se añade la acción Abrir al menú Archivo.
    mnuArchivo_->addAction(actArchivoAbrir_);

    //Se inicializa la acción Abrir Streaming (URL).
    actArchivoAbrirStreaming_ = new QAction(tr("Abrir &Streaming (URL)"), this);
    actArchivoAbrirStreaming_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    //Se añade la acción Abrir Streaming (URL) al menú Archivo.
    mnuArchivo_->addAction(actArchivoAbrirStreaming_);

    //--------------------

    //----AYUDA----------
    mnuAyuda_ = new QMenu(tr("A&yuda"), this);
    //Se añade la opción Ayuda a la barra de menú.
    mainMenu_->addMenu(mnuAyuda_);
    actAyudaAcercade_ = new QAction(tr("Ac&erca de..."), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::Key_F1));
    mnuAyuda_->addAction(actAyudaAcercade_);
    //--------------------

    //----VER----------
    mnuVer_ = new QMenu(tr("&Ver"), this);
    //Se añade la opción Ver a la barra de menú.
    mainMenu_->addMenu(mnuVer_);

    actVerMetadatos_ = new QAction(tr("&Metadatos"), this);
    actVerMetadatos_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnuVer_->addAction(actVerMetadatos_);
    //--------------------


    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));    
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    //Al mover la barra de desplazamiento del vídeo se ejecutará onSeek().
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));    
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    //Menú Archivo
    //Al pinchar sobre Abrir se invocará el slot (método) onOpen().
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(onOpen()));
    //Al pinchar sobre Abrir Streaming (URL) se invocará el slot (método) onOpenStreaming().
    connect(actArchivoAbrirStreaming_, SIGNAL(triggered()), this, SLOT(onOpenStreaming()));

    //Menú Ayuda
    //Al pinchar sobre "Acerca de" se invocará el slot (método) onAcercade().
    connect(actAyudaAcercade_, SIGNAL(triggered()), this, SLOT(onAcercaDe()));

    //Menú Ver
    //Al pinchar sobre "Metadatos" se invocará el slot (método) onMetadatos().
    connect(actVerMetadatos_, SIGNAL(triggered()), this, SLOT(onMetadatos()));

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
        //Para stream:
        //mediaPlayer_->setMedia(QUrl(ventana.getURL()));
    }
}

void MainWindow::onOpenStreaming()
{

    //Se crea al diálogo de tipo "openStreamingDialog" que permitirá introducir la URL que se quiere reproducir por streaming en el
    // reproductor.
    openStreamingDialog openStreamingVentana(this);
    openStreamingVentana.exec();

    //Cuando se cierra la ventana se ejecutarán las siguientes líneas:
    //Se obtiene la url que se ha introducido en el cuadro de texto.
    //La ventana se puede cerrar en la X o pulsando en el botón "btnConfirmarURL", pues así se ha programado en la
    // parte del diseñador.
    QString URL = openStreamingVentana.getURL();

    if (URL != "") {
        //Se indica al reproductor cual es su origen de datos.
        mediaPlayer_->setMedia(QUrl(URL));
        //Ejemplo: http://stream.electroradio.ch:26630/
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

void MainWindow::onMetadatos()
{
    //Se crea el diálogo de tipo "metadaDialog" que muetra los metados del archivo cargado en el reproductor.
    metadaDialog meta(mediaPlayer_, this);
    meta.exec();
}

void MainWindow::onAcercaDe()
{
       //Se crea el diálogo de tipo "QDialogMensaje" que muestra la información que queramos.
       QDialogMensaje dialogMensaje("Alberto AG", this);
       dialogMensaje.exec();
}
