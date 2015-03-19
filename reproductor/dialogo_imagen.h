// Aplicación realizada por Adrián Rodríguez Bazaga
// alu0100826456@ull.edu.es
// Curso de QT: Reproductor


#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#define SLIDER_RANGE 8

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWindowControl>
#include "mainwindow.h"
#include <QDebug>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QMediaPlayer* player, QVideoWidget *video, QWidget *parent = 0);
    ~ImageDialog();

private:
    Ui::ImageDialog *ui;


};

#endif // IMAGEDIALOG_H
