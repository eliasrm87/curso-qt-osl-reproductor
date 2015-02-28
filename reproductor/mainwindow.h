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
#include <QDialog>
#include <QMessageBox>
#include <QLabel>



class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QMenuBar*           mainMenu_;
    QMenu*              mnuArchivo_;
    QAction*            actArchivoAbrir_;
    QAction*            actArchivoSalir_;
    QAction*            actArchivoFullScreen_;
    QMenu*              mnuVer_;
    QAction*            actVerMetadata_;
    QMenu*              mnuAyuda_;
    QAction*            actAyudaAcercade_;
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
    QToolButton*        btnFullScreen_;
    QGridLayout*        lytAcercade_;
    QWidget*            wgtAcercade_;
    QLabel*             imgAcercade_;
    QLabel*             txtAcercade_;

    QString             fileName;

private slots:
    void onOpen();
    void onExit();
    void onMetadata();
    void onAcercade();
    void onSeek();
    void onFullScreen();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);

};

#endif // MAINWINDOW_H
