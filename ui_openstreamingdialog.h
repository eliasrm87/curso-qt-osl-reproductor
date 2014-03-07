/********************************************************************************
** Form generated from reading UI file 'openstreamingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENSTREAMINGDIALOG_H
#define UI_OPENSTREAMINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_openStreamingDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *txtURL;
    QPushButton *btnConfirmarURL;

    void setupUi(QDialog *openStreamingDialog)
    {
        if (openStreamingDialog->objectName().isEmpty())
            openStreamingDialog->setObjectName(QStringLiteral("openStreamingDialog"));
        openStreamingDialog->resize(492, 72);
        gridLayout_2 = new QGridLayout(openStreamingDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        txtURL = new QLineEdit(openStreamingDialog);
        txtURL->setObjectName(QStringLiteral("txtURL"));

        gridLayout->addWidget(txtURL, 0, 0, 1, 1);

        btnConfirmarURL = new QPushButton(openStreamingDialog);
        btnConfirmarURL->setObjectName(QStringLiteral("btnConfirmarURL"));

        gridLayout->addWidget(btnConfirmarURL, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(openStreamingDialog);
        QObject::connect(btnConfirmarURL, SIGNAL(pressed()), openStreamingDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(openStreamingDialog);
    } // setupUi

    void retranslateUi(QDialog *openStreamingDialog)
    {
        openStreamingDialog->setWindowTitle(QApplication::translate("openStreamingDialog", "Dialog", 0));
        btnConfirmarURL->setText(QApplication::translate("openStreamingDialog", "Confirmar", 0));
    } // retranslateUi

};

namespace Ui {
    class openStreamingDialog: public Ui_openStreamingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENSTREAMINGDIALOG_H
