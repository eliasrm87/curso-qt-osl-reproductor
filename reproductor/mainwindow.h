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
#include <QDesktopWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "metadatadialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void GuardarDireccionArchivo(QString line);
    void CargarRecientes();
    void StreamingRadio();
    ~MainWindow();
    
private:

    MetadataDialog *md_;

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
    QKeyEvent*          keyEvent_;
    QString             fileOpen_;

    // Barra de Menu
    QMenuBar   *mainMenu_;

    // Menu -> Archivo
    QMenu      *mnuArchivo_;
    QAction    *actAbrir_;
    QMenu      *mnuRecientes_;
    QAction    *actReciente_;
    QMenu      *mnuStreamingRadio_;
    QAction    *actRadioMaximaFM_;

    // Menu -> Ver
    QMenu      *mnuVer_;
    QAction    *actPantallaCompleta_;
    QAction    *actSalirPantallaCompleta_;
    QAction    *actMetadatos_;

    // Menu -> Ayuda
    QMenu      *mnuAyuda_;
    QAction    *actAcercaDe_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void alAcercaDe();
    void PantallaCompleta();
    void SalirPantallaCompleta();
    void PulsarReciente();
    void MetaDatos();
    void MaximaFM();
};

#endif // MAINWINDOW_H
