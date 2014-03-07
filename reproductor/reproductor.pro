#-------------------------------------------------
#
# Project created by QtCreator 2013-06-20T13:23:33
#
#-------------------------------------------------

QT       += core network xml multimedia multimediawidgets widgets


TARGET = reproductor-exe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    mdatos.cpp \
    dialogforstreaming.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    mdatos.h \
    dialogforstreaming.h

RESOURCES += \
    resources.qrc

FORMS += \
    dialog.ui \
    mdatos.ui \
    dialogforstreaming.ui


