/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <my_qlabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    my_qlabel *pictureFrame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QWidget *label_color;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QPushButton *openFile;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1622, 665);
        MainWindow->setMinimumSize(QSize(0, 0));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, -1, 1619, 641));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pictureFrame = new my_qlabel(horizontalLayoutWidget);
        pictureFrame->setObjectName(QStringLiteral("pictureFrame"));
        pictureFrame->setEnabled(true);
        pictureFrame->setMinimumSize(QSize(0, 0));
        pictureFrame->setMouseTracking(true);
        pictureFrame->setLayoutDirection(Qt::LeftToRight);
        pictureFrame->setFrameShape(QFrame::Box);
        pictureFrame->setPixmap(QPixmap(QString::fromUtf8("../../../../Pictures/print_kittens.jpg")));
        pictureFrame->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(pictureFrame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_color = new QWidget(horizontalLayoutWidget);
        label_color->setObjectName(QStringLiteral("label_color"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_color->sizePolicy().hasHeightForWidth());
        label_color->setSizePolicy(sizePolicy);
        label_color->setMinimumSize(QSize(20, 20));
        label_color->setMaximumSize(QSize(20, 20));
        label_color->setAutoFillBackground(true);

        horizontalLayout_2->addWidget(label_color);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(250, 0));
        lineEdit->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMaximumSize(QSize(250, 16777215));
        pushButton_2->setFlat(false);

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        openFile = new QPushButton(horizontalLayoutWidget);
        openFile->setObjectName(QStringLiteral("openFile"));
        openFile->setMinimumSize(QSize(250, 0));
        openFile->setMaximumSize(QSize(250, 16777215));

        verticalLayout->addWidget(openFile);

        scrollArea = new QScrollArea(horizontalLayoutWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(250, 500));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 231, 498));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pictureFrame->raise();
        pictureFrame->raise();

        verticalLayout->addWidget(scrollArea);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(250, 16777215));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1622, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pictureFrame->setText(QString());
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Label Name", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Label", 0));
        openFile->setText(QApplication::translate("MainWindow", "Open Picture", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Save to Text File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
