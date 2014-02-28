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

//mis includes
#include <QMediaPlaylist>
#include <QKeySequence>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QDialog>
#include <QListWidget>


#include <QTextStream>
#include <QInputDialog>

#include <QLabel>


#include <metadatadialog.h>


const QString nombre = "recientes.txt";


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

    //VIDEO SLIDERS

    QSlider* brightnessSlider_;
    QSlider* contrastSlider_;
    QSlider* saturavionSlider_;

    QToolButton*        btnMinimizar_;



    //botones nuevos tareas
    QToolButton* btnAleatoria_;
    QToolButton* btnBucle_;

    QString nombreArchivo_;



    //montamos el menu Archivo
    QMenuBar *main_menu_;

    //menu Archivo
    QMenu *menu_archivo_;
    QAction *Abrir_;

    //recientes
    QAction *Recientes_;
   // QMenu *rrecientes_;
    QAction *Cerrar_Recientes_;
    QListWidget *lista_recientes_;

    QInputDialog *inputDialog_;
    QAction *Cargar_Lista_Reproduccion_;
    QMediaContent lista_;


    QMediaPlaylist *playlist_;


    QAction *Salir_;





    //menu ver
    QMenu *menu_ver_;
    //pantalla completa
    QAction *Ver_pantalla_completa_;
    QAction *pantalla_completa_deshacer_;

    QAction *Metadatas_;

    QMenu *menu_editar_;
    QAction *Editar_;


    //ayuda
    QAction *Ayuda_;
    QDialog *Mensaje_ayuda_;









private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);

    //menu archivo
    void Abrir();
    void Ayuda();
    void Recientes_crear(QString nombreArchivo);
    void Recientes_leer();
    void Play_recientes(QListWidgetItem *);
    void Cerrar_Recientes();

    void Cargar_lista_reproduccion();

    void Ver_controles_edicion();

    //menu ver
    void Pantalla_completa();
    void Deshacer_pantalla_completa();
    void Ver_metadatos();

    //botones nuevos
    void Aleatoria();
    void Bucle();

    void Minimizar();

    void Salir();

};

#endif // MAINWINDOW_H
