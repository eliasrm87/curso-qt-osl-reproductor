#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>

namespace Ui {
class metadataDialog;
}

class metadataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit metadataDialog(QMediaPlayer *player, QWidget *parent = 0);
    ~metadataDialog();

private:
    Ui::metadataDialog *ui;
    QMediaPlayer* player_;
    void addMetadata(QString key);
};

#endif // METADATADIALOG_H
