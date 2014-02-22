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
#include <QAction>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>
#include <QStringList>
#include <QListWidget>
#include <QDockWidget>
#include <QMediaMetaData>

#include "metadatadialog.h"


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
    QToolButton*        btnFull_;
    QMenuBar*           mainMenu_;
    QMenu*              mnuArchivo_;
    QMenu*              mnuAyuda_;
    QMenu*              mnuVer_;
    QMenu*              mnuArchivoRecientes_;
    QMenu*              mnuVerMetadatos_;

    QAction*            actMetaDatos_;
    QAction*            actArchivoSalir_;
    QAction*            actAyudaAcerca_;
    QAction*            actVerFull_;

    QDockWidget*       dock_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void acerca();
    void pantallaCompleta(QMouseEvent *event);
    void pantallaCompleta();
    void mostrarRecientes();
    void setReciente();
    void mostrarMetadata();

};

#endif // MAINWINDOW_H
