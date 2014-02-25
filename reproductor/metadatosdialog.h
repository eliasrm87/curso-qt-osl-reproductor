#ifndef METADATOSDIALOG_H
#define METADATOSDIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>

namespace Ui {
class MetadatosDialog;
}

class MetadatosDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MetadatosDialog(QMediaPlayer* player, QWidget *parent = 0);
    ~MetadatosDialog();

private:
    Ui::MetadatosDialog *ui;
};

#endif // METADATOSDIALOG_H
