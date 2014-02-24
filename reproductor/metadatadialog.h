#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>

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
    void addMetadata(QString key);
};

#endif // METADATADIALOG_H
