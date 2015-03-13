#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);


    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actArchivoAbrir_->setIcon(QIcon(":/icons/resources/play.png"));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoLista_ = new QAction(tr("&Abrir Lista"), this);
    actArchivoLista_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actArchivoLista_->setIcon(QIcon(":/icons/resources/play.png"));
    mnuArchivo_->addAction(actArchivoLista_);

    actArchivoStream_ = new QAction(tr("&Stream"), this);
    actArchivoStream_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actArchivoStream_->setIcon(QIcon(":/icons/resources/play.png"));
    mnuArchivo_->addAction( actArchivoStream_);

    actArchivoRecientes_ = new QAction(tr("&Recientes"), this);
    actArchivoRecientes_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    mnuArchivo_->addAction(actArchivoRecientes_);

    lista_recientes_ = new QListWidget();
    playlist_ = new QMediaPlaylist();

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuVer_ = new QMenu(tr("&Ver"), this);
    mainMenu_->addMenu(mnuVer_);

    actVerFullScreen_ = new QAction(tr("&FullScreen"), this);
    actVerFullScreen_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    mnuVer_->addAction(actVerFullScreen_);

    actVerMetadatos_ = new QAction(tr("&Metadatos"), this);
    actVerMetadatos_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnuVer_->addAction(actVerMetadatos_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("&Acerca de"), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    mnuAyuda_->addAction(actAyudaAcercade_);

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
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
    lytMain_->addWidget(mainMenu_,  0, 0, 1, 0);
    lytMain_->addWidget(videoWidget_,  1, 0, 1, 5);
    lytMain_->addWidget(playerSlider_, 2, 0, 1, 5);
    lytMain_->addWidget(btnOpen_,      3, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      3, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     3, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      3, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 3, 4, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    //Connections
    connect(actArchivoAbrir_,   SIGNAL(triggered()),        this,         SLOT(onOpen()));
    connect(actArchivoLista_,   SIGNAL(triggered()),        this,         SLOT(Cargar_lista_reproduccion()));
    connect(actArchivoSalir_,   SIGNAL(triggered()),        this,         SLOT(close()));
    connect(actArchivoStream_,  SIGNAL(triggered()),        this,         SLOT(onStream()));
    connect(actArchivoRecientes_,SIGNAL(triggered()),       this,         SLOT(onRecientes()));
    connect(actVerFullScreen_,  SIGNAL(triggered()),        this,         SLOT(onFullscreen()));
    connect(actVerMetadatos_,   SIGNAL(triggered()),        this,         SLOT(onMetadatos()));
    connect(actAyudaAcercade_,  SIGNAL(triggered()),        this,         SLOT(onAcercade()));
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open file"));
    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
//        fileName.section("/",-1);
        mediaPlayer_->play();

        playlist_->addMedia(QUrl::fromLocalFile(fileName));

        Recientes_crear(fileName);

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


void MainWindow::Cargar_lista_reproduccion()
{

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
    }
}


void MainWindow::onStream()//Echarle un vistazo
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Stream"),tr("Direccion:"), QLineEdit::Normal,"", &ok);
    if (ok){
       //mediaPlayer_->setMedia(QUrl("http://vpr.streamguys.net/vpr64.mp3"));
        mediaPlayer_->setMedia(QUrl(text));
    }

}

void MainWindow::onRecientes()
{
    lista_recientes_->clear();
    lista_recientes_->setVisible(true);

    QFile archivo(nombre);

    if (archivo.open(QFile::ReadOnly | QIODevice::Text)) {

        QTextStream in(&archivo);

        while (!in.atEnd()) {
            QString Line = in.readLine();

            lista_recientes_->addItem(new QListWidgetItem(Line));

            connect(lista_recientes_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(Play_recientes(QListWidgetItem *)));

        }

        archivo.close();
    }

}

void MainWindow::Play_recientes(QListWidgetItem *item){

    mediaPlayer_->setMedia(QUrl::fromLocalFile(item->text()));
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
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}

void MainWindow::onFullscreen()
{
        videoWidget_->setFullScreen(true);
}

void MainWindow::onMetadatos(){
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Metadatos");
    wgtAcercade_ = new QWidget(this);
    lytAcercade_ = new QGridLayout(wgtAcercade_);
    dialog->setLayout(lytAcercade_);
    QLabel *texto_ = new QLabel;

    if (mediaPlayer_->isMetaDataAvailable())
    {
        QString t="";
        foreach(QString md, mediaPlayer_->availableMetaData()){
            t+=md;
            t+=" : ";
            t+=mediaPlayer_->metaData(md).toString();
            t+= "\n";
        }
        qDebug()<<t;
        texto_->setText(t);
    }
    else
    {
      texto_->setText("No metadata.");
    }

    lytAcercade_->addWidget(texto_, 0, 1);
    dialog->show();
    dialog->resize(250, 250);
}

void MainWindow::onAcercade(){
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Acerca de");
    wgtAcercade_ = new QWidget(this);
    lytAcercade_ = new QGridLayout(wgtAcercade_);
    dialog->setLayout(lytAcercade_);

    QLabel *myimage_ = new QLabel();
    myimage_->setBackgroundRole(QPalette::Dark);
    myimage_->setScaledContents(true);

    QPixmap pix(":/icons/resources/eject.png");
    myimage_->setPixmap(pix);
    lytAcercade_->addWidget(myimage_, 0, 0);

    QLabel *texto_ = new QLabel;
    texto_->setTextFormat(Qt::RichText);
    texto_->setText("Nombre de empresa");

    lytAcercade_->addWidget(texto_, 0, 1);

    dialog->show();
    dialog->resize(250, 250);
}
