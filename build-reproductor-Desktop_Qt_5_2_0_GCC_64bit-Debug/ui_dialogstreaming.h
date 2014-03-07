/********************************************************************************
** Form generated from reading UI file 'dialogstreaming.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSTREAMING_H
#define UI_DIALOGSTREAMING_H

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

class Ui_DialogStreaming
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;

    void setupUi(QDialog *DialogStreaming)
    {
        if (DialogStreaming->objectName().isEmpty())
            DialogStreaming->setObjectName(QStringLiteral("DialogStreaming"));
        DialogStreaming->resize(400, 105);
        gridLayout_2 = new QGridLayout(DialogStreaming);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(DialogStreaming);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        lineEdit = new QLineEdit(DialogStreaming);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DialogStreaming);

        QMetaObject::connectSlotsByName(DialogStreaming);
    } // setupUi

    void retranslateUi(QDialog *DialogStreaming)
    {
        DialogStreaming->setWindowTitle(QApplication::translate("DialogStreaming", "Dialog", 0));
        pushButton->setText(QApplication::translate("DialogStreaming", "Aceptar", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogStreaming: public Ui_DialogStreaming {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSTREAMING_H
