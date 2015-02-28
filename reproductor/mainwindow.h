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

#include <QAction>
#include <QMenuBar>
#include <QMenu>

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
    QWidget*            aboutWindow;

    QMenuBar*           mainMenu_;
    QMenu*              fileMenu_;
      QAction*            openAct_;
      QMenu*              recentMenu_;
      QActionGroup*       recentFiles_;
    QMenu*              viewMenu_;
      QAction*            fullscreenAct_;
      QAction*            metadataAct_;
    QMenu*              helpMenu_;
      QAction*            aboutAct_;

    void addRecentFile(QString fileName);
    void openFile(QString fileName);

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onOpenRecent(QAction* act);
    void onFullScreen();
    void onMetadataTriggered();
    void onAboutTriggered();
};

#endif // MAINWINDOW_H
