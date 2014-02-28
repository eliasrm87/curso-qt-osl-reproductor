#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>

#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>

#include <QMediaMetaData>
#include <metadatadialog.h>

#include <iostream>
#include <fstream>

using namespace std;

const QString recientes_="recientes.url";

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QGridLayout*        lytMain_;
    QWidget*            wgtMain_;
    QMediaPlayer*       mediaPlayer_;
    QSlider*            playerSlider_;
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_;
    QToolButton*        btnOpen_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;


    //Variables de menu
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoSalir_;
    QMenu *rrecientes_;
    QAction *actRec_;
    QAction* actArchivoRecientes_;
    QMenu *mnuVer_;
    QAction* actMetadatos_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcerca_;


private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);

    void rAbrir();
    void rSalir();
    void rguardar_Recientes(QString ultimo);
    void rmostrar_Recientes();
    void rAcercaDe();
    void rMetadatos();
    void onOpen_streaming(QString cad);
};


#endif // MAINWINDOW_H
