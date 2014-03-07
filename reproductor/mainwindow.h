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
#include <QMouseEvent>
#include <QEvent>
#include <QInputDialog>
#include <metadatadialog.h>
#include <aboutdialog.h>

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

    // Barra de menú
    QMenuBar *mainMenu_;

    // Elementos del menú
    QMenu *mnuArchivo_;
    QMenu *mnuArchivoRecientes_;
    QMenu *mnuVer_;
    QMenu *mnuAyuda_;
    QMenu *mnuStreaming_;

    // Acciones de Archivo
    QAction *actArchivoAbrir_;
    QAction *actArchivoBorrarRecientes_;

    // Acciones de Ver
    QAction *actVerPantallaCompleta_;
    QAction *actVerMetadatos_;

    // Acciones de Ayuda
    QAction *actAyudaAcercaDe_;

    // Acciones de Streaming
    QAction *actStreamingReproducir_;
    QString maximaFM_;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    bool eventFilter(QObject *obj, QEvent *event);
    void pantallaCompleta();
    void showMetadata();
    void alAcercade();

    // Nota: Si la ruta del archivo es demasiado larga
    // el menú contextual se come toda la pantalla
    void alRecientes();
    void agregarReciente(QString archivo);
    void abrirReciente();
    void borrarRecientes();
    void alStreaming();

};

#endif // MAINWINDOW_H
