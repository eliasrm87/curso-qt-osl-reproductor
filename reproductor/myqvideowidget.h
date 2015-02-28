#ifndef MYQVIDEOWIDGET_H
#define MYQVIDEOWIDGET_H
#include <QVideoWidget>
//#include <QEvent>
#include <QKeyEvent>
class myQvideoWidget : public QVideoWidget
{
public:
    myQvideoWidget();
    ~myQvideoWidget();
protected:
    bool event(QEvent *event);
};

#endif // MYQVIDEOWIDGET_H
