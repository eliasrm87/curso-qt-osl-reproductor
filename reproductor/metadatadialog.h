#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QWidget>

namespace Ui {
class MetadataDialog;
}

class MetadataDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MetadataDialog(QWidget *parent = 0);
    ~MetadataDialog();

private:
    Ui::MetadataDialog *ui;
};

#endif // METADATADIALOG_H
