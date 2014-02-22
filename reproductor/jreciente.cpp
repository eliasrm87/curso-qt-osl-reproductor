#include "jreciente.h"

JReciente::JReciente(QObject *parent) :
    QAction(parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(recibeTriggered()));
}

void JReciente::recibeTriggered()
{
    emit pulsado(url_);
}

void JReciente::setURL(QString url)
{
    url_ = url;
    setText(url);
}
