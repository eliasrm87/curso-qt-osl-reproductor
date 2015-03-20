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
#include <QSystemTrayIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    static const unsigned MAX_RECENT_FILES_LENGTH = 10;

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
    QToolButton*        btnRepeat_;
    QToolButton*        btnRandom_;
    QSystemTrayIcon*    trayIcon_;

    QMenuBar*           mainMenu_;
    QMenu*              fileMenu_;
      QAction*            openAct_;
      QMenu*              recentMenu_;
      QActionGroup*       recentFiles_;
    QMenu*              editMenu_;
      QAction*            imageAct_;
    QMenu*              viewMenu_;
      QAction*            fullscreenAct_;
      QAction*            metadataAct_;
    QMenu*              helpMenu_;
      QAction*            aboutAct_;
    QMenu*              trayMenu_;
      QAction*            minimizeAct_;
      QAction*            maximizeAct_;
      QAction*            restoreAct_;
      QAction*            quitAct_;

    void readRecentFileList();
    void writeRecentFileList();
    void addRecentFile(QString fileName);

    void openFile(QString fileName);
    void openM3UPlaylist(QString fileName);
    void openPLSPlaylist(QString fileName);

    QString getFileContents(QString fileName);
    QMediaContent mediaFromString(QString fileNameOrURL);

private slots:
    void onOpen();
    void onSeek();
    void onRepeatChange(bool checked);
    void onRandomChange(bool checked);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onOpenRecent(QAction* act);
    void onFullScreen();
    void onMetadataTriggered();
    void onAboutTriggered();
    void onImageTriggered();

};

#endif // MAINWINDOW_H
