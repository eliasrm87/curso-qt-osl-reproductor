#-------------------------------------------------
#
# Project created by QtCreator 2013-06-20T13:23:33
#
#-------------------------------------------------

QT       += core network xml multimedia multimediawidgets widgets


TARGET = reproductor-arb-exe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogo_url.cpp \
    dialogo_imagen.cpp

HEADERS  += mainwindow.h \
    dialogo_url.h \
    dialogo_imagen.h

RESOURCES += \
    resources.qrc

FORMS += \
    urldialog.ui \
    imagedialog.ui


