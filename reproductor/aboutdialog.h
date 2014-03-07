#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>


class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

signals:

private slots:

private:
    QLabel *acercaDe_;
    QDialogButtonBox *buttonBox_;
    QVBoxLayout *mainLayout_;

};

#endif // ABOUTDIALOG_H
