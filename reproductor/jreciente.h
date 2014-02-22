#ifndef JRECIENTE_H
#define JRECIENTE_H

#include <QAction>

class JReciente : public QAction
{
    Q_OBJECT
public:
    explicit JReciente(QObject *parent = 0);

signals:
    void pulsado (QString url);

public slots:
    void recibeTriggered();

private:
    QString url_;

public:
    void setURL (QString url);
};

#endif // JRECIENTE_H
