#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWindowControl>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QMediaPlayer *player, QWidget *parent = 0);
    ~ImageDialog();

private:
    Ui::ImageDialog *ui;

private slots:
    void onBrilloChanged(int brillo);
    void onContrasteChanged(int constraste);
    void onSaturacionChanged(int saturacion);
};

#endif // IMAGEDIALOG_H
