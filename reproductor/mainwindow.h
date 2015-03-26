#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QString>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include "myqvideowidget.h"
#include <QHeaderView>
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    
private:
    // Menu, actions, Toolbar
    QMenuBar        *mainMenu_;
    QMenu           *mnuFile_;
    QAction         *actFileOpen_;
    QMenu           *mnuRecent_;
    QMenu           *mnuRecentMusic_;
    QMenu           *mnuRecentVideo_;
    QMenu           *mnuRecentStreaming_;
    QAction         *actFileQuit_;
    QMenu           *mnuView_;
    QAction         *actFullScreen_;
    QAction         *actFullScreenQuit_;
    QAction         *actMetaData_;
    QMenu           *mnuHelp_;
    QAction         *actHelpAbout_;
    QToolBar        *mainToolBar_;
    // Dialogs, MessagesBox
    QMessageBox     *msgOpen_;
    QPushButton     *btnSourceLocal_;
    QPushButton     *btnSourceStreaming_;
    QMessageBox     *msgQuit_;
    QDialog         *dlgMetaData_;
    QDialog         *dlgAbout_;
    QGridLayout     *lytAbout_;
    QLabel          *lblAboutIcon_;
    QLabel          *lblAboutText_;
    // User configuration
    QString         *pathUser_;
    QDir            *dirUser_;
    QFile           *fileUser_;
    QMap<QString, QAction*> *lstActsRecentMusic_;
    QMap<QString, QAction*> *lstActsRecentVideo_;
    QMap<QString, QAction*> *lstActsRecentStreaming_;
    // Media player
    QGridLayout     *lytMain_;
    QWidget         *wgtMain_;
    QMediaPlayer    *mediaPlayer_;
    QTableWidget    *tblWgtMetada_;
    QSlider         *playerSlider_;
    MyQVideoWidget  *videoWidget_;
    QSlider         *volumeSlider_;
    QToolButton     *btnOpen_;
    QToolButton     *btnPlay_;
    QToolButton     *btnPause_;
    QToolButton     *btnStop_;

private slots:
    void onOpen();
    void onRecent();
    void onAbout();
    void onMetaData();
    void onFullScreen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onMetaDataAvailable(bool available);

private:
    void createMenu();
    void createToolBar();
    void createMainWidget();
    void createConnections();
    void createDialogs();
    void userConfig();
    void createMetaData();
    void destroyMetaData();
    void createJSON();
    bool readJSON();
    bool writeJSON();


};

#endif // MAINWINDOW_H
