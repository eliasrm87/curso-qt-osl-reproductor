/********************************************************************************
** Form generated from reading UI file 'mdatos.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDATOS_H
#define UI_MDATOS_H

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

class Ui_MDatos
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushCerrar;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;

    void setupUi(QDialog *MDatos)
    {
        if (MDatos->objectName().isEmpty())
            MDatos->setObjectName(QStringLiteral("MDatos"));
        MDatos->resize(400, 300);
        gridLayout_2 = new QGridLayout(MDatos);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushCerrar = new QPushButton(MDatos);
        pushCerrar->setObjectName(QStringLiteral("pushCerrar"));

        gridLayout->addWidget(pushCerrar, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        listWidget = new QListWidget(MDatos);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MDatos);
        QObject::connect(pushCerrar, SIGNAL(pressed()), MDatos, SLOT(close()));

        QMetaObject::connectSlotsByName(MDatos);
    } // setupUi

    void retranslateUi(QDialog *MDatos)
    {
        MDatos->setWindowTitle(QApplication::translate("MDatos", "Dialog", 0));
        pushCerrar->setText(QApplication::translate("MDatos", "Cerar", 0));
    } // retranslateUi

};

namespace Ui {
    class MDatos: public Ui_MDatos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDATOS_H
