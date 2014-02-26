/********************************************************************************
** Form generated from reading UI file 'metadadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METADADIALOG_H
#define UI_METADADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_metadaDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *btnCerrar;
    QSpacerItem *horizontalSpacer;
    QListWidget *listMetada;

    void setupUi(QDialog *metadaDialog)
    {
        if (metadaDialog->objectName().isEmpty())
            metadaDialog->setObjectName(QStringLiteral("metadaDialog"));
        metadaDialog->resize(400, 300);
        gridLayout_2 = new QGridLayout(metadaDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnCerrar = new QPushButton(metadaDialog);
        btnCerrar->setObjectName(QStringLiteral("btnCerrar"));

        gridLayout->addWidget(btnCerrar, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        listMetada = new QListWidget(metadaDialog);
        listMetada->setObjectName(QStringLiteral("listMetada"));

        gridLayout->addWidget(listMetada, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(metadaDialog);
        QObject::connect(btnCerrar, SIGNAL(pressed()), metadaDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(metadaDialog);
    } // setupUi

    void retranslateUi(QDialog *metadaDialog)
    {
        metadaDialog->setWindowTitle(QApplication::translate("metadaDialog", "Dialog", 0));
        btnCerrar->setText(QApplication::translate("metadaDialog", "Cerrar", 0));
    } // retranslateUi

};

namespace Ui {
    class metadaDialog: public Ui_metadaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METADADIALOG_H
