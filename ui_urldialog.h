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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_UrlDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *btnAbrir;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *UrlDialog)
    {
        if (UrlDialog->objectName().isEmpty())
            UrlDialog->setObjectName(QStringLiteral("UrlDialog"));
        UrlDialog->resize(400, 107);
        gridLayout_2 = new QGridLayout(UrlDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAbrir = new QPushButton(UrlDialog);
        btnAbrir->setObjectName(QStringLiteral("btnAbrir"));

        gridLayout->addWidget(btnAbrir, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        lineEdit = new QLineEdit(UrlDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 2);

        label = new QLabel(UrlDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(UrlDialog);
        QObject::connect(btnAbrir, SIGNAL(pressed()), UrlDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(UrlDialog);
    } // setupUi

    void retranslateUi(QDialog *UrlDialog)
    {
        UrlDialog->setWindowTitle(QApplication::translate("UrlDialog", "Dialog", 0));
        btnAbrir->setText(QApplication::translate("UrlDialog", "Abrir", 0));
        label->setText(QApplication::translate("UrlDialog", "Introduce la URL a reproducir", 0));
    } // retranslateUi

};

namespace Ui {
    class UrlDialog: public Ui_UrlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URLDIALOG_H
