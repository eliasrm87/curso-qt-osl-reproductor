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
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "metadatadialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    //Todos widget menos mediaPlayer
    QGridLayout*        lytMain_;
    QWidget*            wgtMain_;
    QMediaPlayer*       mediaPlayer_; //
    QSlider*            playerSlider_;
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_;
    QToolButton*        btnOpen_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;
    QString fileOpen_;

    //Añadimos un menu
    QMenuBar* mainMenu_;

    //Submenus de la barra de menu
    QMenu* mnuArchivo_;
    QMenu* mnuVer_;
    QMenu* mnuAyuda_;
    QMenu* mnuArchivoRecientes_;


    //Acciones
    QAction* actArchivoAbrir_;
    QAction* actVerCompleta_;
    QAction* actAyudaAcerca_;
    QAction* actMetadatos_;
    QAction* actArchivoRecientes_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void acerca();
    void pantallaCompleta();
    void verRecientes();
    void guardarReciente(QString linea);
    void metadatos();
    void pulsarRecientes();

};

#endif // MAINWINDOW_H
