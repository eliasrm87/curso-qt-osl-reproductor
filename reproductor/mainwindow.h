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
#include <QLabel>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFile>
#include <QLineEdit>
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:

    //Variable que revisa si estamos en pantalla completa

    QGridLayout*        lytMain_;
    QWidget*            wgtMain_;
    QMediaPlayer*       mediaPlayer_;
    QSlider*            playerSlider_;
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;
    QLabel*             label_name;

    //Menu
    QMenuBar*           mnBar_;
    QMenu*              mainMenu_;
    QAction*            actAbrir_;
    QMenu*              mnuRecientes_;
    // Acciones de Archivo
    QAction *actArchivoAbrir_;
    QAction *actArchivoBorrarRecientes_;

    QMenu*              mnAyuda_;
    QAction*            actAyuda_;
    QMenu*              mnVer_;
    QAction*            actFullscreen_;
    QAction*            actMetadatos_;

    //LiveStream
    QAction*            actLiveStream_;
    QDialog*            diag_LiveStream_;
    QGridLayout*        lyLiveStream_;
    QLabel*             lbLiveStream_;
    QLineEdit*          lndtLiveStream_;


    //Acerca de
    QDialog*            dialog_acer;
    QLabel*             label_1;
    QLabel*             label_2;
    QGridLayout*        layout_acer;


    //Menu de propiedades
    QMenu*              mnprop_;
    QAction*            actConfig_;
    QDialog*            diag_prop_;
    QGridLayout*        lyprop_;
    QLabel*             lbbrigth_;
    QSlider*            slibright_;
    QLabel*             lbbsatur_;
    QSlider*            slisatur_;
    QLabel*             lbcontrst_;
    QSlider*            slcontrst_;


    //Lista de Reproduccion
    QMediaPlaylist*    play_list;
    QMenu*             mnPlay_list;
    QAction*           addplaylist_;
    QAction*           removeplaylist_;
    QAction*           rdn_play; //Reproduccion Aleatoria
    QAction*           loop_play; //Reproduccion en bucle
    QAction*           btnNext_;
    QAction*           btnAfter_;
    QAction*           showPlaylist_;
private slots:

    void onFullScreen();
    void onLive();
    void onBrightChanged(qint64);
    void onSaturationChanged(qint64);
    void onContrastChanged(qint64);
    void onPropiedades();
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onHelp();

    //Funciones para archivos recientes
    void onRecent();
    void addRecent(QString);
    void opRecent();
    void remRecent();

    //Funcion para controlar la pantalla completa
    bool eventFilter(QObject*, QEvent*);


    //SLOTS PARA LA GESTION DE LA LISTA DE REPRODUCCION
    void onShowPlaylist();
    void start_playlist();
    void addToPlaylist(QString);
    void removeFromPlaylist();
    void onRandom();
    void onLoop();
    void onAdd();
    void onRemove();
    void onNext();
    void onAfter();
};

#endif // MAINWINDOW_H
