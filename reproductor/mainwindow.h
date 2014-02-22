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
#include <QEvent>
#include <QMouseEvent>
#include <QSettings>
#include <QStringList>
#include <QDebug>
#include <QSignalMapper>

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

    QMenuBar*           mbarMenu_;
    QMenu*              mnuFile_;
    QMenu*              mnuView_;
    QMenu*              mnuRecents_;
    QAction*            actOpen_;
    QAction*            actFullScreen_;

    QSettings*          setConfig_;
    QStringList         lstRecents_;
    QSignalMapper*      mapperRecents_;

    bool eventFilter(QObject *obj, QEvent *event);
    void createRecentFiles();

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);

    void onFullScreen();
    void onRecent(QAction *act);
};

#endif // MAINWINDOW_H
