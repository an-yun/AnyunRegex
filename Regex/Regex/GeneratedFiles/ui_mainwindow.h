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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *regex_lib_widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *regex_select_combox;
    QLabel *regex_tip_label;
    QFrame *regex_frame;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *regex_textEdit;
    QFrame *search_result_frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *time_label;
    QLabel *group_label;
    QTextEdit *search_result_textEdit;
    QFrame *searc_frame;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *search_textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        regex_lib_widget = new QWidget(centralWidget);
        regex_lib_widget->setObjectName(QStringLiteral("regex_lib_widget"));
        regex_lib_widget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(regex_lib_widget->sizePolicy().hasHeightForWidth());
        regex_lib_widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(regex_lib_widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        regex_select_combox = new QComboBox(regex_lib_widget);
        regex_select_combox->setObjectName(QStringLiteral("regex_select_combox"));
        regex_select_combox->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(regex_select_combox->sizePolicy().hasHeightForWidth());
        regex_select_combox->setSizePolicy(sizePolicy1);
        regex_select_combox->setMinimumSize(QSize(350, 26));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        regex_select_combox->setFont(font);
        regex_select_combox->setEditable(false);

        horizontalLayout->addWidget(regex_select_combox);

        regex_tip_label = new QLabel(regex_lib_widget);
        regex_tip_label->setObjectName(QStringLiteral("regex_tip_label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        regex_tip_label->setFont(font1);
        regex_tip_label->setStyleSheet(QStringLiteral(""));
        regex_tip_label->setTextFormat(Qt::AutoText);
        regex_tip_label->setScaledContents(true);

        horizontalLayout->addWidget(regex_tip_label);


        verticalLayout->addWidget(regex_lib_widget);

        regex_frame = new QFrame(centralWidget);
        regex_frame->setObjectName(QStringLiteral("regex_frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(regex_frame->sizePolicy().hasHeightForWidth());
        regex_frame->setSizePolicy(sizePolicy2);
        regex_frame->setFrameShape(QFrame::NoFrame);
        regex_frame->setFrameShadow(QFrame::Plain);
        regex_frame->setLineWidth(0);
        regex_frame->setMidLineWidth(0);
        horizontalLayout_2 = new QHBoxLayout(regex_frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        regex_textEdit = new QTextEdit(regex_frame);
        regex_textEdit->setObjectName(QStringLiteral("regex_textEdit"));
        QFont font2;
        font2.setFamily(QStringLiteral("Consolas"));
        font2.setPointSize(10);
        regex_textEdit->setFont(font2);
        regex_textEdit->setFrameShape(QFrame::Panel);
        regex_textEdit->setFrameShadow(QFrame::Sunken);
        regex_textEdit->setLineWidth(1);
        regex_textEdit->setMidLineWidth(1);

        horizontalLayout_2->addWidget(regex_textEdit);

        search_result_frame = new QFrame(regex_frame);
        search_result_frame->setObjectName(QStringLiteral("search_result_frame"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(search_result_frame->sizePolicy().hasHeightForWidth());
        search_result_frame->setSizePolicy(sizePolicy3);
        search_result_frame->setMinimumSize(QSize(500, 0));
        search_result_frame->setFrameShape(QFrame::StyledPanel);
        search_result_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(search_result_frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        time_label = new QLabel(search_result_frame);
        time_label->setObjectName(QStringLiteral("time_label"));
        time_label->setFont(font1);

        verticalLayout_3->addWidget(time_label);

        group_label = new QLabel(search_result_frame);
        group_label->setObjectName(QStringLiteral("group_label"));
        group_label->setFont(font1);

        verticalLayout_3->addWidget(group_label);

        search_result_textEdit = new QTextEdit(search_result_frame);
        search_result_textEdit->setObjectName(QStringLiteral("search_result_textEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(search_result_textEdit->sizePolicy().hasHeightForWidth());
        search_result_textEdit->setSizePolicy(sizePolicy4);
        search_result_textEdit->setFont(font2);
        search_result_textEdit->setFrameShape(QFrame::Panel);
        search_result_textEdit->setFrameShadow(QFrame::Plain);
        search_result_textEdit->setLineWidth(1);
        search_result_textEdit->setReadOnly(true);

        verticalLayout_3->addWidget(search_result_textEdit);


        horizontalLayout_2->addWidget(search_result_frame);


        verticalLayout->addWidget(regex_frame);

        searc_frame = new QFrame(centralWidget);
        searc_frame->setObjectName(QStringLiteral("searc_frame"));
        sizePolicy2.setHeightForWidth(searc_frame->sizePolicy().hasHeightForWidth());
        searc_frame->setSizePolicy(sizePolicy2);
        searc_frame->setFrameShape(QFrame::NoFrame);
        searc_frame->setFrameShadow(QFrame::Plain);
        searc_frame->setMidLineWidth(1);
        verticalLayout_2 = new QVBoxLayout(searc_frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        search_textEdit = new QTextEdit(searc_frame);
        search_textEdit->setObjectName(QStringLiteral("search_textEdit"));
        search_textEdit->setFont(font2);
        search_textEdit->setFrameShape(QFrame::Panel);
        search_textEdit->setLineWidth(1);
        search_textEdit->setMidLineWidth(1);

        verticalLayout_2->addWidget(search_textEdit);


        verticalLayout->addWidget(searc_frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(regex_select_combox, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(regex_selected_changed(int)));
        QObject::connect(regex_textEdit, SIGNAL(textChanged()), MainWindow, SLOT(regex_text_changed()));
        QObject::connect(search_textEdit, SIGNAL(textChanged()), MainWindow, SLOT(search_text_changed()));
        QObject::connect(search_textEdit, SIGNAL(cursorPositionChanged()), MainWindow, SLOT(regex_text_cursor_position_changed()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "C++ Regex Tool", Q_NULLPTR));
        regex_select_combox->clear();
        regex_select_combox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "C++ Boost.Regex 5.1.2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "C++ std::regex (Visual C++ 2015)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Qt 5.8 QRegExp", Q_NULLPTR)
         << QApplication::translate("MainWindow", "C++ anyun_regex", Q_NULLPTR)
        );
        regex_select_combox->setCurrentText(QApplication::translate("MainWindow", "C++ Boost.Regex 5.1.2", Q_NULLPTR));
        regex_tip_label->setText(QString());
        regex_textEdit->setPlaceholderText(QApplication::translate("MainWindow", "please enter your regex expression", Q_NULLPTR));
        time_label->setText(QApplication::translate("MainWindow", "\347\224\250\346\227\266: 0.000000s", Q_NULLPTR));
        group_label->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204\345\206\205\345\256\271", Q_NULLPTR));
        search_textEdit->setPlaceholderText(QApplication::translate("MainWindow", "please enter your text", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
