#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QListWidget>

namespace Ui {
class MetadataDialog;
}

class MetadataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MetadataDialog(QMediaPlayer *player, QWidget *parent = 0);
    ~MetadataDialog();

private:
    Ui::MetadataDialog *ui;
    QMediaPlayer *player_;
    QStringList metadatosDisponibles_;
    void addMetadata(QStringList metadatos);
};

#endif // METADATADIALOG_H
