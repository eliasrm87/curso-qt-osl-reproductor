// Aplicación realizada por Adrián Rodríguez Bazaga
// alu0100826456@ull.edu.es
// Curso de QT: Reproductor


#ifndef URLDIALOG_H
#define URLDIALOG_H

#include <QDialog>

namespace Ui {
class UrlDialog;
}

class UrlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UrlDialog(QWidget *parent = 0);
    ~UrlDialog();

private:
    Ui::UrlDialog *ui;
    QString url_;

public slots:
    QString getNuevaUrl();
};

#endif // URLDIALOG_H
