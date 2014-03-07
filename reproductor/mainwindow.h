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
#include <QMenu>
#include <QMenuBar>

#include "qdialogmensaje.h"
#include "metadadialog.h"
#include "openstreamingdialog.h"

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
    QSlider*            playerSlider_; //barra de posición de reproducción de vídeo
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_; //barra de sonido
    QToolButton*        btnOpen_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;

    //Barra de menú.
    QMenuBar* mainMenu_;

    //Opción Archivo para la barra de menú.
    QMenu* mnuArchivo_;
    //Acción Abrir del menú Archivo.
    QAction* actArchivoAbrir_;
    //Acción Abrir Streaming (URL) del menú Archivo.
    QAction* actArchivoAbrirStreaming_;

    //Opción Ayuda para la barra de menú.
    QMenu* mnuAyuda_;
    //Acción "Acerca de" del menú Ayuda.
    QAction* actAyudaAcercade_;

    //Opción Ver para la barra de menú.
    QMenu* mnuVer_;
    //Acción Metadatos del menú Ver.
    QAction* actVerMetadatos_;

private slots:
    void onOpen();
    void onOpenStreaming();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);    
    void onVolumeChanged(int volume);
    void onAcercaDe();
    void onMetadatos();
};

#endif // MAINWINDOW_H
