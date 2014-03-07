/********************************************************************************
** Form generated from reading UI file 'dialogforstreaming.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFORSTREAMING_H
#define UI_DIALOGFORSTREAMING_H

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

class Ui_DialogforStreaming
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushOk;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;

    void setupUi(QDialog *DialogforStreaming)
    {
        if (DialogforStreaming->objectName().isEmpty())
            DialogforStreaming->setObjectName(QStringLiteral("DialogforStreaming"));
        DialogforStreaming->resize(400, 75);
        gridLayout_2 = new QGridLayout(DialogforStreaming);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushOk = new QPushButton(DialogforStreaming);
        pushOk->setObjectName(QStringLiteral("pushOk"));

        gridLayout->addWidget(pushOk, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        lineEdit = new QLineEdit(DialogforStreaming);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DialogforStreaming);

        QMetaObject::connectSlotsByName(DialogforStreaming);
    } // setupUi

    void retranslateUi(QDialog *DialogforStreaming)
    {
        DialogforStreaming->setWindowTitle(QApplication::translate("DialogforStreaming", "Dialog", 0));
        pushOk->setText(QApplication::translate("DialogforStreaming", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogforStreaming: public Ui_DialogforStreaming {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFORSTREAMING_H
