#include "myqvideowidget.h"

MyQVideoWidget::MyQVideoWidget(QMediaPlayer *parent) :
  parent(parent)
{
}

bool	MyQVideoWidget::event(QEvent * event) {

  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = (QKeyEvent*)event;
    switch (keyEvent->key()) {
      case Qt::Key_Escape:
      case Qt::Key_End:
        changeFullScreen();
        break;
      case Qt::Key_Space:
        switch (parent->state()) {
          case QMediaPlayer::PlayingState:
            parent->pause();
            break;
          case QMediaPlayer::PausedState:
          default:
            parent->play();
            break;
        }
        break;
      case Qt::CTRL + Qt::Key_Left:
        parent->stop();
        parent->play();
        break;
    }
  }
  event->accept();
  return QVideoWidget::event(event);
}

void MyQVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
  changeFullScreen();
  event->accept();
}

void MyQVideoWidget::changeFullScreen()
{
  setFullScreen(!isFullScreen());
}
