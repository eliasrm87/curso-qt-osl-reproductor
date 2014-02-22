#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>

namespace Ui {
class MetaDataDialog;
}

class MetaDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MetaDataDialog(QMediaPlayer* player, QWidget *parent = 0);
    ~MetaDataDialog();

private:
    Ui::MetaDataDialog *ui;
    QMediaPlayer* player_;

    void addMetadata(QString key);
};

#endif // METADATADIALOG_H
