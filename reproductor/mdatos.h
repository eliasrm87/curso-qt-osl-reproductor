#ifndef MDATOS_H
#define MDATOS_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>

namespace Ui {
class MDatos;
}

class MDatos : public QDialog
{
    Q_OBJECT

public:
    explicit MDatos(QMediaPlayer* player,QWidget *parent = 0);
    ~MDatos();

private:
    Ui::MDatos *ui;
    QMediaPlayer * player_;

};

#endif // MDATOS_H
