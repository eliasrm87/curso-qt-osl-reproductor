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
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QInputDialog>
#include <QListWidget>
#include <QSystemTrayIcon>
#include <QMediaPlaylist>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QMenuBar*           mainMenu_;
    QMenu*              mnuArchivo_;
    QAction*            actArchivoAbrir_;
    QAction*            actArchivoStreaming_;
    QAction*            actArchivosRecientes_;
    QAction*            actArchivoSalir_;
    QAction*            actArchivoFullScreen_;
    QMenu*              mnuVer_;
    QAction*            actVerMetadata_;
    QAction*            actArchivoRecientes_;
    QMenu*              mnuAyuda_;
    QAction*            actAyudaAcercade_;
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
    QToolButton*        btnRepeat_;
    QToolButton*        btnShuffle_;
    QToolButton*        btnFullScreen_;
    QGridLayout*        lytAcercade_;
    QWidget*            wgtAcercade_;
    QLabel*             imgAcercade_;
    QLabel*             txtAcercade_;
    QListWidget*        listaRecientes_;
    QString             fileName;
    QSystemTrayIcon*    trayIcon;
    QMenu*              trayIconMenu;
    QAction*            minimizeAction;
    QAction*            maximizeAction;
    QAction*            restoreAction;
    QMediaPlaylist*     playlist_;

private slots:
    void onOpen();
    void onExit();
    void onMetadata();
    void onRecientes();
    void add2Recientes (QString filename);
    void onAcercade();
    void onStreaming();
    void onSeek();
    void onFullScreen();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onRepeat();
    void onShuffle();
    void createActions();
    void createTrayIcon();
};

#endif // MAINWINDOW_H
