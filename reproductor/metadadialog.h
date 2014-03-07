#ifndef METADADIALOG_H
#define METADADIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>

namespace Ui {
class metadaDialog;
}

class metadaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit metadaDialog(QMediaPlayer* player, QWidget *parent = 0);
    ~metadaDialog();

private:
    Ui::metadaDialog *ui;    
};

#endif // METADADIALOG_H
