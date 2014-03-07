#ifndef DIALOGSTREAMING_H
#define DIALOGSTREAMING_H

#include <QDialog>

namespace Ui {
class DialogStreaming;
}

class DialogStreaming : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStreaming(QWidget *parent = 0);
    ~DialogStreaming();

private:
    Ui::DialogStreaming *ui;
};

#endif // DIALOGSTREAMING_H
