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
#include <jdialog.h>
#include <QList>
#include <QString>
#include <jreciente.h>
#include <QVariant>
#include <QMessageBox>
#include <QMediaMetaData>
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

    QMenuBar*           barMenu_;
    QMenu*              mnuArchivo_;
    QAction*            actArchivoAbrir_;

    QMenu*              mnuAyuda_;
    QAction*            actAyudaAcerca_;

    QMenu*              mnuVer_;
    QAction*            actFullScreen_;
    bool                estadoFS_;

    QMenu*              mnuRecientes_;
    QList<QString>*     listaFav_;

    QAction*            actVerMetadatos_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onAcercaDe();
    void abrirReciente(QString url);
    void verMetadatos();

signals:
    void fullScreen(bool);

private slots:
    void escuchaActFS();
};

#endif // MAINWINDOW_H
