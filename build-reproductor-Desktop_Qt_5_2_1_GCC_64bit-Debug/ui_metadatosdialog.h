/********************************************************************************
** Form generated from reading UI file 'metadatosdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METADATOSDIALOG_H
#define UI_METADATOSDIALOG_H

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

class Ui_MetadatosDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;

    void setupUi(QDialog *MetadatosDialog)
    {
        if (MetadatosDialog->objectName().isEmpty())
            MetadatosDialog->setObjectName(QStringLiteral("MetadatosDialog"));
        MetadatosDialog->resize(400, 305);
        gridLayout_2 = new QGridLayout(MetadatosDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(MetadatosDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        listWidget = new QListWidget(MetadatosDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MetadatosDialog);
        QObject::connect(pushButton, SIGNAL(pressed()), MetadatosDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(MetadatosDialog);
    } // setupUi

    void retranslateUi(QDialog *MetadatosDialog)
    {
        MetadatosDialog->setWindowTitle(QApplication::translate("MetadatosDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("MetadatosDialog", "Cerrar", 0));
    } // retranslateUi

};

namespace Ui {
    class MetadatosDialog: public Ui_MetadatosDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METADATOSDIALOG_H
