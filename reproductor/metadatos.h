#ifndef METADADATOS_H
#define METADADATOS_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class MetadaDatos;
}

class MetadaDatos : public QDialog
{
    Q_OBJECT

public:
    explicit MetadaDatos(QMediaPlayer* player,QWidget *parent = 0);
    ~MetadaDatos();

private:
    Ui::MetadaDatos *ui;
};

#endif // METADADATOS_H
