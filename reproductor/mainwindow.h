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
#include <QMessageBox>
#include <QMediaMetaData>
#include "aboutdialog.h"
#include "metadatosdialog.h"

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
    // var menu
    QMenuBar*           mainMenu_;
    QMenu*              mnuArchivo_;
    QMenu*              mnuVer_;
    QMenu*              mnuAyuda_;
    QAction*            actAbrir_;
    QMenu*              actRecientes_;
    QAction*            actFullScreen_;
    QAction*            actMetadatos_;
    QAction*            actAcercaDe_;
    QStringList         recentsList;                // lista de recientes
    QMenu*              actStreaming_;
    QAction*            actRtve_;



private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    // own slots
    void alAcercade();
    void alFullScreen();
    void saveRecent(QString dirFile);
    void readRecentsVideos();
    void PulsarReciente();
    void alMetadato();
    void alRtve();

};

#endif // MAINWINDOW_H
