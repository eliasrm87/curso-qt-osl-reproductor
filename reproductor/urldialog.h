#ifndef URLDIALOG_H
#define URLDIALOG_H

#include <QDialog>

namespace Ui {
class URLDialog;
}

class URLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit URLDialog(QWidget *parent = 0);
    ~URLDialog();

private:
    Ui::URLDialog *ui;
};

#endif // URLDIALOG_H
