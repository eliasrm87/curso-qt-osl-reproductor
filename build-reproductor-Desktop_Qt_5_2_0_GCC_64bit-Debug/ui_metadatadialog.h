/********************************************************************************
** Form generated from reading UI file 'metadatadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METADATADIALOG_H
#define UI_METADATADIALOG_H

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

class Ui_MetaDataDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *botonCerrar;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;

    void setupUi(QDialog *MetaDataDialog)
    {
        if (MetaDataDialog->objectName().isEmpty())
            MetaDataDialog->setObjectName(QStringLiteral("MetaDataDialog"));
        MetaDataDialog->resize(400, 300);
        gridLayout_2 = new QGridLayout(MetaDataDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        botonCerrar = new QPushButton(MetaDataDialog);
        botonCerrar->setObjectName(QStringLiteral("botonCerrar"));

        gridLayout->addWidget(botonCerrar, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        listWidget = new QListWidget(MetaDataDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MetaDataDialog);
        QObject::connect(botonCerrar, SIGNAL(pressed()), MetaDataDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(MetaDataDialog);
    } // setupUi

    void retranslateUi(QDialog *MetaDataDialog)
    {
        MetaDataDialog->setWindowTitle(QApplication::translate("MetaDataDialog", "Dialog", 0));
        botonCerrar->setText(QApplication::translate("MetaDataDialog", "Cerrar", 0));
    } // retranslateUi

};

namespace Ui {
    class MetaDataDialog: public Ui_MetaDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METADATADIALOG_H
