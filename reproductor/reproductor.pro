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
    metadatadialog.cpp \
    urldialog.cpp \
    imagedialog.cpp

HEADERS  += mainwindow.h \
    metadatadialog.h \
    urldialog.h \
    imagedialog.h

RESOURCES += \
    resources.qrc

FORMS += \
    metadatadialog.ui \
    urldialog.ui \
    imagedialog.ui


