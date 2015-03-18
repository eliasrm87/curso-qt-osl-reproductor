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
#include <QtEvents>
#include <QLabel>
#include <QInputDialog>
#include <QLineEdit>
#include "recientes.h"

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

    //crear menu //incluir librerias <QMenu>
    QMenuBar*       mainMenu_;

    //descripcion de opciones de menu //incluir librerias <QMenuBar>
    QMenu*          mnuArchivo_;
    QMenu*          mnuHelp_;
    QMenu*          mnuVer_;

    //acciones de menu
    QAction*        actArchivoAbrir_;
    QAction* actSalir_;
    QAction* actAbout_;
    QAction* actfullscreen_;
    QAction* actRecientes_;
    QAction* actmetadatos_;
    QAction* actstreaming_;

    QString url_example_;

protected:
    bool event(QEvent *evento);

private slots:
    void onOpen();
    void onExit();
    void onAbout();
    void onSeek();
    void fullScreen();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void metadatos();

    void toStreaming();

};

#endif // MAINWINDOW_H
