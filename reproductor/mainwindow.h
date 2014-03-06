#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaMetaData>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>
#include "dialog.h"
#include "mdatos.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QAction *           abrir_;
    Dialog *            dialog_;
    QAction *           AcercaDe_;
    QAction *           PantCom_;
    QAction *           verMetadatos_;
    QAction *           str_;
    QMenu    *          menuArchivo_;
    QMenu   *           menuAyuda_;
    QMenu  *            ver_;
    QMenu *             recientes_;
    QMenu *             metadatos_;
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

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void acercade_s();
    void fullScreen_s();
    void meta_s();
    void open_str();

};

#endif // MAINWINDOW_H
