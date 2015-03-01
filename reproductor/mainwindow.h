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
    QFile*              fich_recent;

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

    QString             file_name;
    QLabel*             label_name;
    QListWidget*        play_list;


    //Menu
    QMenuBar*           mnBar_;
    QMenu*              mainMenu_;
    QAction*            actAbrir_;
    QAction*            actRecientes_;
    QAction*            live_stream;
    QDialog*            live_diag;
    QGridLayout*        ly_livestream;
    QLabel             live_lb;
    QLineEdit          live_lnedit;


    QMenu*              mnAyuda_;
    QAction*            actAyuda_;
    QMenu*              mnVer_;
    QAction*            actFullscreen_;
    QAction*            actMetadatos_;

    //Acerca de
    QDialog*            dialog_acer;
    QLabel*             label_1;
    QLabel*             label_2;
    QGridLayout*        layout_acer;


//    //Menu de propiedades
//    QMenu*              mnprop_;
//    QAction*            actConfig_;
//    QDialog*            diag_prop_;
//    QGridLayout*        lyprop_;
//    QLabel*             lbbrigth_;
//    QSlider*            slibright_;
//    QLabel*             lbbsatur_;
//    QSlider*            slisatur_;
//    QLabel*             lbcontrst_;
//    QSlider*            slcontrst_;



private slots:

//    void onBrightChanged(qint64);
//    void onSaturationChanged(qint64);
//    void onContrastChanged(qint64);
//    void onPropiedades();
    void onLive();
    void onRecent();
    void onSelect();
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onHelp();

protected:
    //void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
