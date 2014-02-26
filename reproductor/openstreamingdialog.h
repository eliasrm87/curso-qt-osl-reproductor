#ifndef OPENSTREAMINGDIALOG_H
#define OPENSTREAMINGDIALOG_H

#include <QDialog>

namespace Ui {
class openStreamingDialog;
}

class openStreamingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit openStreamingDialog(QWidget *parent = 0);
    ~openStreamingDialog();

    QString getURL();

private:
    Ui::openStreamingDialog *ui;
};

#endif // OPENSTREAMINGDIALOG_H
