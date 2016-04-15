/********************************************************************************
** Form generated from reading UI file 'conproddialog.ui'
**
** Created: Mon Apr 11 04:48:09 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONPRODDIALOG_H
#define UI_CONPRODDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConProdDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QProgressBar *producerProgressBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QProgressBar *consumerProgressBar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QProgressBar *bufferProgressBar;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;

    void setupUi(QDialog *ConProdDialog)
    {
        if (ConProdDialog->objectName().isEmpty())
            ConProdDialog->setObjectName(QString::fromUtf8("ConProdDialog"));
        ConProdDialog->resize(375, 155);
        verticalLayout = new QVBoxLayout(ConProdDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(ConProdDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        producerProgressBar = new QProgressBar(ConProdDialog);
        producerProgressBar->setObjectName(QString::fromUtf8("producerProgressBar"));
        producerProgressBar->setValue(24);

        horizontalLayout->addWidget(producerProgressBar);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ConProdDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        consumerProgressBar = new QProgressBar(ConProdDialog);
        consumerProgressBar->setObjectName(QString::fromUtf8("consumerProgressBar"));
        consumerProgressBar->setValue(24);

        horizontalLayout_2->addWidget(consumerProgressBar);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(ConProdDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_3->addWidget(label);

        bufferProgressBar = new QProgressBar(ConProdDialog);
        bufferProgressBar->setObjectName(QString::fromUtf8("bufferProgressBar"));
        bufferProgressBar->setValue(24);

        horizontalLayout_3->addWidget(bufferProgressBar);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        startButton = new QPushButton(ConProdDialog);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout_4->addWidget(startButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(ConProdDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(ConProdDialog);
        QObject::connect(pushButton_3, SIGNAL(clicked()), ConProdDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(ConProdDialog);
    } // setupUi

    void retranslateUi(QDialog *ConProdDialog)
    {
        ConProdDialog->setWindowTitle(QApplication::translate("ConProdDialog", "ConProdDialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ConProdDialog", "Produced", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConProdDialog", "Consumed", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConProdDialog", "Current Buffer Level", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("ConProdDialog", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("ConProdDialog", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConProdDialog: public Ui_ConProdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONPRODDIALOG_H
