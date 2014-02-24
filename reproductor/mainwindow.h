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

//Añadidos para las tareas propuestas
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QMediaMetaData>
#include "metadatadialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

/*Todos los widgets declarados a continuación.
Menos QMediaPlayer. Tener en cuenta que se establece un widget para la posición central:
wgtMain_*/

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

    //Añadido para hacer las tareas propuestas
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoRecientes_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcercade_;
    QMenu* mnuVer_;
    QAction* actVerPantallacompleta_;
    QAction* actVerMetadatos_;
    QAction* actVerMaximaFM_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);

    //Añadido para las tareas propuestas
    void alRecientes();
    void alAcercade();
    void alPantallacompleta();
    void alMetadatos();
    void alMaximaFM();

};

#endif // MAINWINDOW_H
