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
#include <QAction>
 #include <QToolBar>
#include <QDialog>
#include <QFile>
#include<QString>

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
    QMenuBar*       mainmenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuVer_;
    QAction*        actVerpc_;
    QMenu*        actArchivosRecientes_;
    QAction*        actVerMetadatos_;
    QMenu*          mnuAyuda_;
    QAction*        actAcercade_;
    QToolBar*       toolbar_;
    QDialog*        ventana_;
    QAction*        actescape_;
    QAction*       actArchivoAbrir_;
    QAction*       actminimizar_;
    QString       line;
    QAction*       minimizar_;
private slots:
    void es();
    void pc();
    void dialog();
    void alSalir();
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void minimizar();
    void recientes();
    void metadatos();
    void onOpenrecientes();
};

#endif // MAINWINDOW_H
