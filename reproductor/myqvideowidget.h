#ifndef MYQVIDEOWIDGET_H
#define MYQVIDEOWIDGET_H

#include <QVideoWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>

class MyQVideoWidget : public QVideoWidget
{
  public:
    MyQVideoWidget(QMediaPlayer *parent = 0);

 protected:
    bool event(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);

  private:
    QMediaPlayer *parent;
    void changeFullScreen();
};

#endif // MYQVIDEOWIDGET_H
