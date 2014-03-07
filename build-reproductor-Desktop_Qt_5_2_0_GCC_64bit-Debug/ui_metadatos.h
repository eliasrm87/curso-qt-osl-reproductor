/********************************************************************************
** Form generated from reading UI file 'metadatos.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METADATOS_H
#define UI_METADATOS_H

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

class Ui_MetadaDatos
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushCerrar;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;

    void setupUi(QDialog *MetadaDatos)
    {
        if (MetadaDatos->objectName().isEmpty())
            MetadaDatos->setObjectName(QStringLiteral("MetadaDatos"));
        MetadaDatos->resize(400, 300);
        gridLayout_2 = new QGridLayout(MetadaDatos);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushCerrar = new QPushButton(MetadaDatos);
        pushCerrar->setObjectName(QStringLiteral("pushCerrar"));

        gridLayout->addWidget(pushCerrar, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        listWidget = new QListWidget(MetadaDatos);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MetadaDatos);
        QObject::connect(pushCerrar, SIGNAL(pressed()), MetadaDatos, SLOT(close()));

        QMetaObject::connectSlotsByName(MetadaDatos);
    } // setupUi

    void retranslateUi(QDialog *MetadaDatos)
    {
        MetadaDatos->setWindowTitle(QApplication::translate("MetadaDatos", "Dialog", 0));
        pushCerrar->setText(QApplication::translate("MetadaDatos", "Cerar", 0));
    } // retranslateUi

};

namespace Ui {
    class MetadaDatos: public Ui_MetadaDatos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METADATOS_H
