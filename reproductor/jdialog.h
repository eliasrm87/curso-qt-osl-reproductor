#ifndef JDIALOGO_H
#define JDIALOGO_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QLabel>

class JDialog : public QDialog
{
    Q_OBJECT
public:
    explicit JDialog(QWidget *parent = 0);

private:
    QPushButton* aceptar_;
    QGridLayout* layout_;
};

#endif // JDIALOGO_H
