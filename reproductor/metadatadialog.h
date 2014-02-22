#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QString>
#include <QMediaPlayer>
#include <QMediaMetaData>

namespace Ui {
class MetadataDialog;
}

class MetadataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MetadataDialog(QMediaPlayer* player, QWidget *parent = 0);
    ~MetadataDialog();

private:
    Ui::MetadataDialog *ui;
};

#endif // METADATADIALOG_H
