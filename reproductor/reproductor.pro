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
    qdialogmensaje.cpp \
    metadadialog.cpp \
    openstreamingdialog.cpp

HEADERS  += mainwindow.h \
    qdialogmensaje.h \
    metadadialog.h \
    openstreamingdialog.h

RESOURCES += \
    resources.qrc

FORMS += \
    metadadialog.ui \
    openstreamingdialog.ui


