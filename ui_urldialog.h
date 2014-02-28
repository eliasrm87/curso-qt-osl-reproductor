/********************************************************************************
** Form generated from reading UI file 'urldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_URLDIALOG_H
#define UI_URLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_URLDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;

    void setupUi(QDialog *URLDialog)
    {
        if (URLDialog->objectName().isEmpty())
            URLDialog->setObjectName(QStringLiteral("URLDialog"));
        URLDialog->resize(336, 119);
        gridLayout_2 = new QGridLayout(URLDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(URLDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        lineEdit = new QLineEdit(URLDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(URLDialog);
        QObject::connect(pushButton, SIGNAL(pressed()), URLDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(URLDialog);
    } // setupUi

    void retranslateUi(QDialog *URLDialog)
    {
        URLDialog->setWindowTitle(QApplication::translate("URLDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("URLDialog", "Aceptar", 0));
    } // retranslateUi

};

namespace Ui {
    class URLDialog: public Ui_URLDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URLDIALOG_H
