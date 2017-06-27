/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *StartSniff;
    QPushButton *StopSniff;
    QLabel *indDevice;
    QPushButton *FindDevice;
    QSpacerItem *horizontalSpacer;
    QCheckBox *SafeInFile;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *qplot;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *buttonAll;
    QRadioButton *buttonTCP;
    QRadioButton *buttonUDP;
    QRadioButton *buttonIGMP;
    QTextEdit *logtrace;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(506, 389);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        StartSniff = new QPushButton(centralWidget);
        StartSniff->setObjectName(QStringLiteral("StartSniff"));

        horizontalLayout->addWidget(StartSniff);

        StopSniff = new QPushButton(centralWidget);
        StopSniff->setObjectName(QStringLiteral("StopSniff"));

        horizontalLayout->addWidget(StopSniff);

        indDevice = new QLabel(centralWidget);
        indDevice->setObjectName(QStringLiteral("indDevice"));
        indDevice->setMinimumSize(QSize(22, 22));
        indDevice->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        horizontalLayout->addWidget(indDevice);

        FindDevice = new QPushButton(centralWidget);
        FindDevice->setObjectName(QStringLiteral("FindDevice"));

        horizontalLayout->addWidget(FindDevice);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        SafeInFile = new QCheckBox(centralWidget);
        SafeInFile->setObjectName(QStringLiteral("SafeInFile"));

        horizontalLayout->addWidget(SafeInFile);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        qplot = new QCustomPlot(centralWidget);
        qplot->setObjectName(QStringLiteral("qplot"));
        qplot->setMinimumSize(QSize(350, 160));

        horizontalLayout_2->addWidget(qplot);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(100, 16777215));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 58, 100));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        buttonAll = new QRadioButton(layoutWidget);
        buttonAll->setObjectName(QStringLiteral("buttonAll"));
        buttonAll->setChecked(true);

        verticalLayout->addWidget(buttonAll);

        buttonTCP = new QRadioButton(layoutWidget);
        buttonTCP->setObjectName(QStringLiteral("buttonTCP"));

        verticalLayout->addWidget(buttonTCP);

        buttonUDP = new QRadioButton(layoutWidget);
        buttonUDP->setObjectName(QStringLiteral("buttonUDP"));

        verticalLayout->addWidget(buttonUDP);

        buttonIGMP = new QRadioButton(layoutWidget);
        buttonIGMP->setObjectName(QStringLiteral("buttonIGMP"));

        verticalLayout->addWidget(buttonIGMP);


        horizontalLayout_3->addWidget(groupBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        logtrace = new QTextEdit(centralWidget);
        logtrace->setObjectName(QStringLiteral("logtrace"));
        logtrace->setMinimumSize(QSize(0, 0));
        logtrace->setMaximumSize(QSize(16777215, 160));
        logtrace->setReadOnly(true);

        verticalLayout_2->addWidget(logtrace);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 506, 19));
        menuBar->setNativeMenuBar(true);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "NetDigger", Q_NULLPTR));
        StartSniff->setText(QApplication::translate("MainWindow", "StartSniff", Q_NULLPTR));
        StopSniff->setText(QApplication::translate("MainWindow", "StopSniff", Q_NULLPTR));
        indDevice->setText(QString());
        FindDevice->setText(QApplication::translate("MainWindow", "Find device", Q_NULLPTR));
        SafeInFile->setText(QApplication::translate("MainWindow", "SafeInFile", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Sniffing protocol", Q_NULLPTR));
        buttonAll->setText(QApplication::translate("MainWindow", "All", Q_NULLPTR));
        buttonTCP->setText(QApplication::translate("MainWindow", "TCP", Q_NULLPTR));
        buttonUDP->setText(QApplication::translate("MainWindow", "UDP", Q_NULLPTR));
        buttonIGMP->setText(QApplication::translate("MainWindow", "ICMP", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
