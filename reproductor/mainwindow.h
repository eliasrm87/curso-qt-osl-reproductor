#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>
#include <QMediaMetaData>
#include <QTextEdit>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QInputDialog>

const QString nombre = "recientes.txt";

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QMenuBar*           mainMenu_;
    QMenu*              mnuArchivo_;
    QMenu*              mnuVer_;
    QMenu*              mnuAyuda_;
    QGridLayout*        lytMain_;
    QWidget*            wgtMain_;
    QGridLayout*        lytAcercade_;
    QWidget*            wgtAcercade_;
    QLabel*             myimage_;
    QLabel*             texto_;
    QMediaPlayer*       mediaPlayer_;
    QSlider*            playerSlider_;
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_;
    QToolButton*        btnOpen_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;
    QAction*            actArchivoAbrir_;
    QAction*            actArchivoLista_;
    QAction*            actArchivoSalir_;
    QAction*            actArchivoStream_;
    QAction*            actArchivoRecientes_;
    QAction*            actVerFullScreen_;
    QAction*            actVerMetadatos_;
    QAction*            actAyudaAcercade_;
    QTextEdit*          txtEditor_;
    QPushButton*        botonOk_;
    QMediaPlaylist*     playlist_;
    QListWidget*        lista_recientes_;
    QInputDialog*       inputDialog_;
    QMediaContent       lista_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onStream();
    void onRecientes();
    void Cargar_lista_reproduccion();
    void Recientes_crear(QString nombreArchivo);
    void Play_recientes(QListWidgetItem *);
    void onFullscreen();
    void onMetadatos();
    void onAcercade();
};

#endif // MAINWINDOW_H
