#ifndef DIALOGFORSTREAMING_H
#define DIALOGFORSTREAMING_H
#include <QUrl>

#include <QDialog>

namespace Ui {
class DialogforStreaming;
}

class DialogforStreaming : public QDialog
{
    Q_OBJECT

public:
    explicit DialogforStreaming(QWidget *parent = 0);
    ~DialogforStreaming();

private slots:
    void on_pushOk_clicked();
signals:
    void s_enviarUrl(QUrl);

private:
    Ui::DialogforStreaming *ui;
};

#endif // DIALOGFORSTREAMING_H
