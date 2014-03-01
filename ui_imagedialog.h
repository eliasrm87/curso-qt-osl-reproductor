/********************************************************************************
** Form generated from reading UI file 'imagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDIALOG_H
#define UI_IMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ImageDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QPushButton *btnAceptar;
    QSpacerItem *horizontalSpacer_2;
    QSlider *barraSaturacion;
    QSlider *barraContraste;
    QSlider *barraBrillo;

    void setupUi(QDialog *ImageDialog)
    {
        if (ImageDialog->objectName().isEmpty())
            ImageDialog->setObjectName(QStringLiteral("ImageDialog"));
        ImageDialog->resize(400, 167);
        gridLayout_2 = new QGridLayout(ImageDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(ImageDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ImageDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 1);

        label_3 = new QLabel(ImageDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        btnAceptar = new QPushButton(ImageDialog);
        btnAceptar->setObjectName(QStringLiteral("btnAceptar"));

        gridLayout_2->addWidget(btnAceptar, 3, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        barraSaturacion = new QSlider(ImageDialog);
        barraSaturacion->setObjectName(QStringLiteral("barraSaturacion"));
        barraSaturacion->setCursor(QCursor(Qt::PointingHandCursor));
        barraSaturacion->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(barraSaturacion, 2, 1, 1, 2);

        barraContraste = new QSlider(ImageDialog);
        barraContraste->setObjectName(QStringLiteral("barraContraste"));
        barraContraste->setCursor(QCursor(Qt::PointingHandCursor));
        barraContraste->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(barraContraste, 1, 1, 1, 2);

        barraBrillo = new QSlider(ImageDialog);
        barraBrillo->setObjectName(QStringLiteral("barraBrillo"));
        barraBrillo->setCursor(QCursor(Qt::PointingHandCursor));
        barraBrillo->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(barraBrillo, 0, 1, 1, 2);


        retranslateUi(ImageDialog);
        QObject::connect(barraBrillo, SIGNAL(sliderMoved(int)), ImageDialog, SLOT(update()));
        QObject::connect(barraContraste, SIGNAL(sliderMoved(int)), ImageDialog, SLOT(update()));
        QObject::connect(barraSaturacion, SIGNAL(sliderMoved(int)), ImageDialog, SLOT(update()));
        QObject::connect(btnAceptar, SIGNAL(pressed()), ImageDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(ImageDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageDialog)
    {
        ImageDialog->setWindowTitle(QApplication::translate("ImageDialog", "Dialog", 0));
        label_2->setText(QApplication::translate("ImageDialog", "Contraste", 0));
        label->setText(QApplication::translate("ImageDialog", "Brillo", 0));
        label_3->setText(QApplication::translate("ImageDialog", "Saturaci\303\263n", 0));
        btnAceptar->setText(QApplication::translate("ImageDialog", "Aceptar", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageDialog: public Ui_ImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDIALOG_H
