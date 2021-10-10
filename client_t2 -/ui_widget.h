/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *send;
    QTextEdit *send_t;
    QTextEdit *recv_t;
    QPushButton *connect;
    QPushButton *disconnect;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        send = new QPushButton(Widget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(70, 450, 101, 41));
        send_t = new QTextEdit(Widget);
        send_t->setObjectName(QString::fromUtf8("send_t"));
        send_t->setGeometry(QRect(60, 300, 181, 141));
        recv_t = new QTextEdit(Widget);
        recv_t->setObjectName(QString::fromUtf8("recv_t"));
        recv_t->setGeometry(QRect(370, 50, 301, 391));
        connect = new QPushButton(Widget);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setGeometry(QRect(90, 140, 101, 41));
        disconnect = new QPushButton(Widget);
        disconnect->setObjectName(QString::fromUtf8("disconnect"));
        disconnect->setGeometry(QRect(90, 200, 101, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        send->setText(QCoreApplication::translate("Widget", "Send", nullptr));
        connect->setText(QCoreApplication::translate("Widget", "connect", nullptr));
        disconnect->setText(QCoreApplication::translate("Widget", "disconnect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
