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

#include <QMessageBox>

#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include <iostream>

#include <metadatadialog.h>

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


    QMenuBar        *mainMenu_;
    QMenu           *menusFile_;
    QAction         *actionOpenFile_;
    QAction         *actionAbout_;

    QMenu           *menusMetadato_;
    QAction         *actionShowMetadata;

    QAction         *actionFullScreen_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);

    void onAbout();
    void onOpen_auto();

    void onFullScreen();

    void onMetadata();
};

#endif // MAINWINDOW_H
