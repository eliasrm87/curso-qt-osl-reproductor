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
    mediaPlayer_  = new QMediaPlayer(this); // Objeto que se encarga del video
    playerSlider_ = new QSlider(Qt::Horizontal, this); // Barra de tiempo de reproducción
    videoWidget_  = new QVideoWidget(this); // Recuadro negro de vídeo
    volumeSlider_ = new QSlider(Qt::Horizontal, this); // Barra de volumen
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_); // Añadir el recuadro al reproductor
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

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));

    // Inicializamos los elementos del menú
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mnuVer_ = new QMenu(tr("&Ver"), this);
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mnuStreaming_ = new QMenu(tr("&Streaming"), this);

    // Añadimos los elementos al menú
    mainMenu_->addMenu(mnuArchivo_);
    mainMenu_->addMenu(mnuVer_);
    mainMenu_->addMenu(mnuAyuda_);
    mainMenu_->addMenu(mnuStreaming_);

    // Inicializamos acciones de los elementos del menú
    // Añadimos las acciones a los elementos
    // Añadimos los shortcuts correspondientes
    actArchivoAbrir_ = new QAction(tr("Abrir..."), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    mnuArchivoRecientes_ = new QMenu(tr("Recientes"), this);
    mnuArchivo_->addMenu(mnuArchivoRecientes_);

    actVerMetadatos_ = new QAction(tr("Metadatos"), this);
    mnuVer_->addAction(actVerMetadatos_);

    actVerPantallaCompleta_ = new QAction(tr("Pantalla completa"), this);
    actVerPantallaCompleta_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F11));
    mnuVer_->addAction(actVerPantallaCompleta_);

    actAyudaAcercaDe_ = new QAction(tr("Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcercaDe_);

    actStreamingReproducir_ = new QAction(tr("Reproducir fuente"), this);
    mnuStreaming_->addAction(actStreamingReproducir_);

    // Añadir barra de menús a la ventana
    setMenuBar(mainMenu_);

    // Conexiones del menú
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(onOpen()));
    connect(actVerPantallaCompleta_, SIGNAL(triggered()), this, SLOT(pantallaCompleta()));
    connect(actVerMetadatos_, SIGNAL(triggered()), this, SLOT(showMetadata()));
    connect(actAyudaAcercaDe_, SIGNAL(triggered()), this, SLOT(alAcercade()));
    connect(actStreamingReproducir_, SIGNAL(triggered()), this, SLOT(alStreaming()));

    // Hace que funcione el eventfilter
    videoWidget_->installEventFilter(this);

    // Mostramos el historial de recientes
    this->alRecientes();

    // Inicializamos una fuente de streaming por defecto
    maximaFM_ = "http://208.92.53.87:80/MAXIMAFM";
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abrir archivo"));

    // Para abrir streaming setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM"))

    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));

        // Reproducir automáticamente
        mediaPlayer_->play();

        // Agregar a recientes
        this->agregarReciente(fileName);

        // Refrescar historial de recientes
        this->alRecientes();
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

void MainWindow::pantallaCompleta()
{
    if(!videoWidget_->isFullScreen()){
        videoWidget_->setFullScreen(true);
    }
    else{
        videoWidget_->setFullScreen(false);
    }
}

//void MainWindow::setRecientes(QString path)
//{
//    actArchivoRecientes_->addAction(new QAction(path, this));
//}

void MainWindow::showMetadata()
{
    MetadataDialog videoData(mediaPlayer_);
    videoData.exec();
}

void MainWindow::alAcercade()
{
    AboutDialog acercaDe;
    acercaDe.exec();
}

void MainWindow::alRecientes()
{
    QFile recientes("../recientes.txt");
    if (recientes.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Eliminamos las acciones (path) del menú si ya se habían añadido
        mnuArchivoRecientes_->clear();

        // Obtenemos las reproducciones recientes
        QTextStream in(&recientes);
        while (!in.atEnd()) {
            QString archivo = in.readLine();
            QAction *actAbrirArchivo = new QAction(archivo, this);
            mnuArchivoRecientes_->addAction(actAbrirArchivo);
            connect(actAbrirArchivo, SIGNAL(triggered()), this, SLOT(abrirReciente()));
        }

        // Si hay acciones recientes, damos opción de borrado
        if (recientes.size() != 0) {
            mnuArchivoRecientes_->addSeparator();
            actArchivoBorrarRecientes_ = new QAction(tr("Borrar historial de recientes"), this);
            mnuArchivoRecientes_->addAction(actArchivoBorrarRecientes_);
            connect(actArchivoBorrarRecientes_, SIGNAL(triggered()), this, SLOT(borrarRecientes()));
        }
        recientes.close();
    }
}

void MainWindow::agregarReciente(QString archivo)
{
    QFile recientes("../recientes.txt");
    if (recientes.open(QIODevice::Append)) {
        QTextStream out(&recientes);
        out << archivo << endl;
        recientes.close();
    }
}

void MainWindow::abrirReciente()
{
    QAction *accion = (QAction*)QObject::sender();
    mediaPlayer_->setMedia(QUrl::fromLocalFile(accion->text()));
    mediaPlayer_->play();
}

void MainWindow::borrarRecientes()
{
    // Vaciamos el fichero de recientes
    QFile recientes("../recientes.txt");
    if (recientes.open(QIODevice::Append | QIODevice::Text)) {
        recientes.resize(0);
        recientes.close();

        // Eliminamos las acciones (path) del menú
        mnuArchivoRecientes_->clear();
    }

    // Refrescamos la barra
    this->alRecientes();
}

void MainWindow::alStreaming()
{
    bool aceptar;

    // Recogemos la fuente de streaming
    QString url = QInputDialog::getText(this, tr("Reproducir fuente de streaming"),
                                                  tr("Introduzca la URL:"),
                                                  QLineEdit::Normal,
                                                  maximaFM_,
                                                  &aceptar);
    QRegExp whiteSpaces("^\\s+$");

    // Se comprueba que la página no esté vacía
    if (aceptar && !url.isEmpty() && !whiteSpaces.exactMatch(url)) {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(url));
        mediaPlayer_->play();
    }
}

// Para poder pillar bien lo de pantalla completa hay que pasar esta
// funcion de event filter, y habilita fullscreen
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
