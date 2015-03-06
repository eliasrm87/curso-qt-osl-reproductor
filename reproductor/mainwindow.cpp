#include "mainwindow.h"
#include <QList>
#include <QLabel>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QSettings>
#include <QTextStream>
#include <QCloseEvent>
#include <QPushButton>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Create menus and actions
    mainMenu_   = new QMenuBar(this);
    fileMenu_   = new QMenu(tr("&Archivo"), this);
    editMenu_   = new QMenu(tr("&Edición"), this);
    recentMenu_ = new QMenu(tr("Archivos recientes"), this);
    viewMenu_   = new QMenu(tr("&Ver"), this);
    helpMenu_   = new QMenu(tr("&Ayuda"), this);
    trayMenu_   = new QMenu(tr("Tray"), this);

    setMenuBar(mainMenu_);
    mainMenu_->addMenu(fileMenu_);
    mainMenu_->addMenu(editMenu_);
    mainMenu_->addMenu(viewMenu_);
    mainMenu_->addMenu(helpMenu_);

    openAct_       = new QAction(tr("&Abrir..."), this);
    recentFiles_   = new QActionGroup(this);
    imageAct_      = new QAction(tr("&Imagen..."), this);
    fullscreenAct_ = new QAction(tr("&Pantalla completa"), this);
    metadataAct_   = new QAction(tr("&Metadatos..."), this);
    aboutAct_      = new QAction(tr("&Acerca de..."), this);
    minimizeAct_   = new QAction(tr("Mi&nimizar"), this);
    maximizeAct_   = new QAction(tr("Ma&ximizar"), this);
    restoreAct_    = new QAction(tr("&Restablecer"), this);
    quitAct_       = new QAction(tr("&Salir"), this);

    fullscreenAct_->setShortcut(Qt::Key_F11);

    fileMenu_->addAction(openAct_);
    fileMenu_->addMenu(recentMenu_);
    editMenu_->addAction(imageAct_);
    viewMenu_->addAction(fullscreenAct_);
    viewMenu_->addAction(metadataAct_);
    helpMenu_->addAction(aboutAct_);
    trayMenu_->addAction(minimizeAct_);
    trayMenu_->addAction(maximizeAct_);
    trayMenu_->addAction(restoreAct_);
    trayMenu_->addSeparator();
    trayMenu_->addAction(quitAct_);

    readRecentFileList();

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);
    btnRepeat_    = new QToolButton(this);
    btnRandom_    = new QToolButton(this);
    trayIcon_     = new QSystemTrayIcon(QIcon(QPixmap(":/icons/resources/play.png")), this);

    QMediaPlaylist* playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);

    //Setup widgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setPlaylist(playlist);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);
    btnRepeat_->setCheckable(true);
    btnRandom_->setCheckable(true);
    trayIcon_->setContextMenu(trayMenu_);
    trayIcon_->setVisible(true);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 7);
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 7);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);
    lytMain_->addWidget(btnRepeat_,    2, 5, 1, 1);
    lytMain_->addWidget(btnRandom_,    2, 6, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));
    btnRepeat_->setIcon(QIcon(QPixmap(":/icons/resources/loop.png")));
    btnRandom_->setIcon(QIcon(QPixmap(":/icons/resources/random.png")));

    // Actions connections
    connect(openAct_,       SIGNAL(triggered()),         this, SLOT(onOpen()));
    connect(imageAct_,      SIGNAL(triggered()),         this, SLOT(onImageTriggered()));
    connect(recentFiles_,   SIGNAL(triggered(QAction*)), this, SLOT(onOpenRecent(QAction*)));
    connect(fullscreenAct_, SIGNAL(triggered()),         this, SLOT(onFullScreen()));
    connect(metadataAct_,   SIGNAL(triggered()),         this, SLOT(onMetadataTriggered()));
    connect(aboutAct_,      SIGNAL(triggered()),         this, SLOT(onAboutTriggered()));

    connect(minimizeAct_,   SIGNAL(triggered()),         this, SLOT(hide()));
    connect(maximizeAct_,   SIGNAL(triggered()),         this, SLOT(showMaximized()));
    connect(restoreAct_,    SIGNAL(triggered()),         this, SLOT(showNormal()));
    connect(quitAct_,       SIGNAL(triggered()),         qApp, SLOT(quit()));

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(btnRepeat_,    SIGNAL(toggled(bool)),           this,         SLOT(onRepeatChange(bool)));
    connect(btnRandom_,    SIGNAL(toggled(bool)),           this,         SLOT(onRandomChange(bool)));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event) {
    writeRecentFileList();

    if (trayIcon_->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::readRecentFileList() {
    QFile file("lastopened.m3u");
    file.open(QFile::ReadOnly);

    if (file.isOpen()) {
        QTextStream in(&file);
        while (!in.atEnd())
            addRecentFile(in.readLine());
        file.close();
    }
}

void MainWindow::writeRecentFileList() {
    QFile file("lastopened.m3u");
    file.open(QFile::WriteOnly);

    if (file.isOpen()) {
        QTextStream out(&file);

        QList<QAction*> recent = recentFiles_->actions();
        for (QList<QAction*>::iterator i = recent.begin(); i != recent.end(); ++i)
            out << (*i)->text() << "\n";

        file.close();
    }
}

void MainWindow::addRecentFile(QString fileName) {
    QAction* fileAct = new QAction(fileName, this);

    QList<QAction*> recent = recentFiles_->actions();
    if (recent.size() == MAX_RECENT_FILES_LENGTH)
      recent.removeFirst();

    for (QList<QAction*>::iterator i = recent.begin(); i != recent.end(); ++i) {
        if ((*i)->text() == fileName)
            return;
    }

    recentMenu_->addAction(fileAct);
    recentFiles_->addAction(fileAct);
}

void MainWindow::openFile(QString fileName) {
    if (!fileName.isEmpty()) {
        mediaPlayer_->playlist()->clear();

        if (fileName.endsWith(".m3u"))
            openM3UPlaylist(fileName);
        else if (fileName.endsWith(".pls"))
            openPLSPlaylist(fileName);
        else
            mediaPlayer_->playlist()->addMedia(mediaFromString(fileName));

        addRecentFile(fileName);
    }
}

void MainWindow::openM3UPlaylist(QString fileName) {
    QStringList lines = getFileContents(fileName).split("\n");
    for (QStringList::iterator i = lines.begin(); i != lines.end(); ++i) {
        QString line = *i;
        if (!line.startsWith('#'))
            mediaPlayer_->playlist()->addMedia(mediaFromString(line));
    }
}

void MainWindow::openPLSPlaylist(QString fileName) {
    QSettings playlist(fileName, QSettings::IniFormat);

    playlist.beginGroup("playlist");
    int numEntries = playlist.value("NumberOfEntries", 0).toInt();
    for (int i = 1; i <= numEntries; i++) {
        QString trackPath = playlist.value(QString("File%1").arg(i)).toString();
        //QString trackTitle = playlist.value(QString("Title%1").arg(i)).toString();
        //int trackLength = playlist.value(QString("Length%1").arg(i), -1).toInt();

        mediaPlayer_->playlist()->addMedia(mediaFromString(trackPath));
    }
    playlist.endGroup();
}

QMediaContent MainWindow::mediaFromString(QString fileNameOrURL) {
    if (!(fileNameOrURL.startsWith("http://") || fileNameOrURL.startsWith("https://")))
        return QUrl::fromLocalFile(fileNameOrURL);

    return QUrl(fileNameOrURL);
}

QString MainWindow::getFileContents(QString fileName) {
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QString contents = file.readAll();
    file.close();

    return contents;
}

void MainWindow::onOpen() {
    //Show file open dialog
    openFile(QFileDialog::getOpenFileName(this, tr("Abrir archivo"), "",
                                          tr("Archivos de sonido (*.mp3 *.wav *.ogg);;"
                                             "Archivos de vídeo (*.avi *.mp4 *.mkv);;"
                                             "Listas de reproducción (*.m3u *.pls)")));
}

void MainWindow::onSeek() {
    mediaPlayer_->setPosition(playerSlider_->sliderPosition());
}

void MainWindow::onRepeatChange(bool checked) {
    QMediaPlaylist* playlist = mediaPlayer_->playlist();

    if (!btnRandom_->isChecked()) {
        if (checked)
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
        else
            playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
}

void MainWindow::onRandomChange(bool checked) {
    QMediaPlaylist* playlist = mediaPlayer_->playlist();

    if (checked)
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    else if (btnRepeat_->isChecked())
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    else
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
}

void MainWindow::onDurationChanged(qint64 duration) {
    playerSlider_->setRange(0, duration);
}

void MainWindow::onPositionChanged(qint64 position) {
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume) {
    mediaPlayer_->setVolume(volume);
}

void MainWindow::onOpenRecent(QAction* act) {
    openFile(act->text());
}

void MainWindow::onFullScreen() {
    videoWidget_->setFullScreen(!videoWidget_->isFullScreen());

    if (videoWidget_->isFullScreen()) {
      videoWidget_->addAction(fullscreenAct_);
      fullscreenAct_->setShortcut(Qt::Key_Escape);
    }
    else {
      videoWidget_->removeAction(fullscreenAct_);
      fullscreenAct_->setShortcut(Qt::Key_F11);
    }
}

void MainWindow::onMetadataTriggered() {
    QStringList metadataProperties = mediaPlayer_->availableMetaData();

    if (metadataProperties.empty()) {
        QMessageBox::information(this, tr("No hay metadatos"),
                                 tr("No hay metadatos disponibles en el fichero actual"));
        return;
    }

    QStringList metadata;
    for (QStringList::iterator str = metadataProperties.begin(); str != metadataProperties.end(); ++str) {
        QVariant data = mediaPlayer_->metaData(*str);
        metadata.append(*str + ": " + data.toString());
    }

    QLayout* metadataLayout = new QGridLayout(this);
    QDialog* metadataDialog = new QDialog(this);
    QLabel* dialogText = new QLabel(metadata.join("\n"), this);

    metadataLayout->addWidget(dialogText);
    metadataDialog->setLayout(metadataLayout);
    metadataDialog->setWindowTitle(tr("Metadatos"));

    metadataDialog->setModal(true);
    metadataDialog->setVisible(true);
    metadataDialog->exec();
}

void MainWindow::onAboutTriggered() {
    QDialog dialog;
    QGridLayout* layout = new QGridLayout(&dialog);

    QLabel* image = new QLabel(&dialog);
    image->setPixmap(QPixmap(":/images/resources/qt.jpg"));
    QLabel* dialogText = new QLabel(tr("Hecho por Sergio Afonso"), &dialog);

    layout->addWidget(image, 0, 0, 1, 1);
    layout->addWidget(dialogText, 0, 1, 1, 1);
    dialog.setLayout(layout);
    dialog.setWindowTitle(tr("Acerca de"));

    dialog.setModal(true);
    dialog.setVisible(true);
    dialog.exec();
}

void MainWindow::onImageTriggered() {
    QDialog dialog;
    QGridLayout* layout = new QGridLayout(&dialog);

    QLabel* brightness = new QLabel(tr("Brillo:"), &dialog);
    QLabel* contrast   = new QLabel(tr("Contraste:"), &dialog);
    QLabel* saturation = new QLabel(tr("Saturación:"), &dialog);

    QSlider* brightnessSlider = new QSlider(Qt::Horizontal, &dialog);
    QSlider* contrastSlider   = new QSlider(Qt::Horizontal, &dialog);
    QSlider* saturationSlider = new QSlider(Qt::Horizontal, &dialog);

    brightnessSlider->setRange(-100, 100);
    contrastSlider->setRange(-100, 100);
    saturationSlider->setRange(-100, 100);

    brightnessSlider->setValue(videoWidget_->brightness());
    contrastSlider->setValue(videoWidget_->contrast());
    saturationSlider->setValue(videoWidget_->saturation());

    QFrame* separator = new QFrame(&dialog);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    QPushButton* okButton = new QPushButton(tr("Aceptar"), &dialog);

    layout->addWidget(brightness,       0, 0, 1, 1);
    layout->addWidget(brightnessSlider, 0, 1, 1, 2);
    layout->addWidget(contrast,         1, 0, 1, 1);
    layout->addWidget(contrastSlider,   1, 1, 1, 2);
    layout->addWidget(saturation,       2, 0, 1, 1);
    layout->addWidget(saturationSlider, 2, 1, 1, 2);
    layout->addWidget(separator,        3, 0, 1, 3);
    layout->addWidget(okButton,         4, 2, 1, 1);

    dialog.setLayout(layout);
    dialog.setWindowTitle(tr("Metadatos"));

    connect(brightnessSlider, SIGNAL(sliderMoved(int)), videoWidget_, SLOT(setBrightness(int)));
    connect(contrastSlider,   SIGNAL(sliderMoved(int)), videoWidget_, SLOT(setContrast(int)));
    connect(saturationSlider, SIGNAL(sliderMoved(int)), videoWidget_, SLOT(setSaturation(int)));
    connect(okButton,         SIGNAL(clicked()),        &dialog,      SLOT(close()));

    dialog.setModal(true);
    dialog.setVisible(true);
    dialog.exec();
}
