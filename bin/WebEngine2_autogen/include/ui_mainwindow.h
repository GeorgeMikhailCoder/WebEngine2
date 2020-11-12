/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <qwebengineview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineAdress;
    QPushButton *ButLoad;
    QWebEngineView *preview;
    QLabel *codePreview;
    QLabel *MsgOut;
    QLineEdit *linePath;
    QToolButton *ButSetPath;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineAdress = new QLineEdit(centralwidget);
        lineAdress->setObjectName(QString::fromUtf8("lineAdress"));
        lineAdress->setGeometry(QRect(10, 20, 331, 22));
        ButLoad = new QPushButton(centralwidget);
        ButLoad->setObjectName(QString::fromUtf8("ButLoad"));
        ButLoad->setGeometry(QRect(260, 50, 81, 28));
        preview = new QWebEngineView(centralwidget);
        preview->setObjectName(QString::fromUtf8("preview"));
        preview->setGeometry(QRect(390, 10, 361, 241));
        codePreview = new QLabel(centralwidget);
        codePreview->setObjectName(QString::fromUtf8("codePreview"));
        codePreview->setGeometry(QRect(390, 270, 361, 251));
        MsgOut = new QLabel(centralwidget);
        MsgOut->setObjectName(QString::fromUtf8("MsgOut"));
        MsgOut->setGeometry(QRect(10, 130, 301, 191));
        MsgOut->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        linePath = new QLineEdit(centralwidget);
        linePath->setObjectName(QString::fromUtf8("linePath"));
        linePath->setGeometry(QRect(10, 50, 211, 22));
        ButSetPath = new QToolButton(centralwidget);
        ButSetPath->setObjectName(QString::fromUtf8("ButSetPath"));
        ButSetPath->setGeometry(QRect(230, 50, 27, 22));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 90, 331, 23));
        progressBar->setValue(24);
        progressBar->setTextVisible(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineAdress->setText(QCoreApplication::translate("MainWindow", "http://miet.aha.ru/", nullptr));
        ButLoad->setText(QCoreApplication::translate("MainWindow", "Download", nullptr));
        codePreview->setText(QCoreApplication::translate("MainWindow", "There will be source code of html", nullptr));
        MsgOut->setText(QCoreApplication::translate("MainWindow", "The messages output", nullptr));
        linePath->setText(QCoreApplication::translate("MainWindow", "C:\\Users\\60\\Desktop\\\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \320\270\320\267 \320\274\320\276\320\265\320\263\320\276 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217\\111.html", nullptr));
        ButSetPath->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
