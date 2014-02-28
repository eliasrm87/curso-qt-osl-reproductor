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
    videoWidget_->setMinimumSize(600, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

//    recientes_="recientes.txt";

    //Menus
    mainMenu_= new QMenuBar(this);
    mnuArchivo_= new QMenu(tr("&Archivo"),this);
    mainMenu_->addMenu(mnuArchivo_);
    setMenuBar(mainMenu_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"),this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    mnuArchivo_->addAction(actArchivoAbrir_);

    rrecientes_= new QMenu(tr("Recientes"),this);
    mnuArchivo_->addMenu(rrecientes_);

    actRec_ = new QAction(tr("&Recargar recientes"),this);
    rrecientes_->addAction(actRec_);
    connect(actRec_, SIGNAL(triggered()),this,SLOT(rmostrar_Recientes()));
//    rrecientes_->addAction(actArchivoSalir_);

/*    actArchivoRecientes_ = new QAction(tr("&Recientes"),this);
    actArchivoRecientes_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    mnuArchivo_->addAction(actArchivoRecientes_);
*/
    actArchivoSalir_ = new QAction(tr("&Salir"),this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuVer_ = new QMenu(tr("&Ver"));
    mainMenu_->addMenu(mnuVer_);

    actMetadatos_ = new QAction(tr("&Metadatos"), this);
    actMetadatos_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnuVer_->addAction(actMetadatos_);

    mnuAyuda_ = new QMenu(tr("A&yuda"));
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcerca_ = new QAction(tr("Acerca de"), this);
    actAyudaAcerca_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1));
    mnuAyuda_->addAction(actAyudaAcerca_);

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
    connect(actArchivoAbrir_, SIGNAL(triggered()),this,SLOT(rAbrir()));

    connect(actMetadatos_, SIGNAL(triggered()),this,SLOT(rMetadatos()));
    connect(actArchivoSalir_, SIGNAL(triggered()),this,SLOT(rSalir()));
    connect(actAyudaAcerca_, SIGNAL(triggered()),this,SLOT(rAcercaDe()));
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
        mediaPlayer_->play();
        rguardar_Recientes(fileName);
    }
}

void MainWindow::onOpen_streaming(QString cad)
{
    mediaPlayer_->setMedia(QUrl(cad));
//    http://208.92.53.87:88/MAXIMAFM
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


void MainWindow::rAbrir()
{
    QString nombreArchivo;
    nombreArchivo= QFileDialog::getOpenFileName(this, tr("Abrir archivo audio/video"),
                                "",tr("Archivos de audio/video (*ogg *mp3 *wma *.avi *.mp4 *.mpeg *.mpg *.wmv *.flv *.mov)"));

    if (nombreArchivo != "")
    {
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly))
        {
            mediaPlayer_->setMedia(QUrl::fromLocalFile(nombreArchivo));
            mediaPlayer_->play();
            archivo.close();
            rguardar_Recientes(nombreArchivo);
        }
    }
}



void MainWindow::rSalir()
{
    QMessageBox msg(this);
    msg.setInformativeText("¿Salir del reproductor?");
    msg.addButton("Si",QMessageBox::YesRole);
    msg.addButton("No",QMessageBox::NoRole);
    if (!msg.exec())
        close();
}

void MainWindow::rguardar_Recientes(QString ultimo)
{
    const unsigned MAX = 4;//Numero de recientes que quiero guardar; x implementar
    QFile archivo;
    archivo.setFileName(recientes_);
    if (archivo.open(QFile::WriteOnly | QFile::Append))
    {
        archivo.write(ultimo.toUtf8());
        archivo.write("\n");
//        QTextStream in(&file);
//        if !line.isNull()
//        while(!in.atEnd()) {
  //          QString line = in.readLine();
//        }
        archivo.close();
    }
    else
    {
        QMessageBox msg(this);
        msg.setWindowTitle(tr("E"));
        msg.setText("<p>Error de acceso a recientes</p>");
        msg.addButton("Aceptar",QMessageBox::AcceptRole);
        if (msg.exec())
            close();
    }
}

void MainWindow::rmostrar_Recientes()
{
    QFile file(recientes_);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString line;
        do {
                line = in.readLine();
                 //string line2 = qstrdup(line.toLatin1());
//                 QTextStream cout(stdout,QIODevice::WriteOnly);
//                 cout<<line<<endl;
                 rrecientes_->addMenu(line);
         } while (!line.isNull());

/*        while(!in.atEnd())
        {
            QString line = in.readLine();
            lista_->addItem(new QListWidgetItem(line));
            item_ = new QListWidgetItem(line, lista_);
            item_->setText(line);
            lista_->insertItem(i,item_);
            i++;
            connect(lista_,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this, SLOT(ir_a(QListWidgetItem *)));
        }*/
        file.close();
    }
}


void MainWindow::rAcercaDe()
{
    QMessageBox msg(this);
    msg.setWindowTitle(tr("Acerca de"));
    msg.setText("<p>MediaPlayer's Aaron (in Qt!)</p><p>v 1.0</p>");
    msg.addButton("Aceptar",QMessageBox::AcceptRole);

    if (msg.exec())
        close();
}

void MainWindow::rMetadatos()
{
    MetadataDialog md(mediaPlayer_,this);
    md.exec();
}
