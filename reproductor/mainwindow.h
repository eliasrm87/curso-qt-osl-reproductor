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
#include <QEvent>
#include <QMouseEvent>
#include "metadatadialog.h"
#include "dialogstreaming.h"
#include <QMediaMetaData>

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
    QMenu*              mnuArchivo_;
    QAction*            actAbrir_;
    QMenu*              mnuVer_;
    QAction*            actFullScreen_;
    QMenu*              mnuRecent_;
    QAction*            actMetaData_;
    QAction*            actStreaming_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onFullScreen();
    bool eventFilter(QObject *obj, QEvent *event);
    void onRecentFiles(QAction *path);
    void onMetaData();
    void onStreaming();
};

#endif // MAINWINDOW_H
