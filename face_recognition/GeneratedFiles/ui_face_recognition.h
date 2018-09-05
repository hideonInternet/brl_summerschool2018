/********************************************************************************
** Form generated from reading UI file 'face_recognition.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_RECOGNITION_H
#define UI_FACE_RECOGNITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_face_recognitionClass
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *home_0;
    QLabel *h_label;
    QLabel *h_RGBpic;
    QLabel *h_Dpic;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *h_name;
    QLabel *h_id;
    QLabel *h_res;
    QPushButton *enroll_button;
    QPushButton *exit_button;
    QLabel *h_threshold;
    QDoubleSpinBox *h_th;
    QLabel *h_name_label;
    QLabel *h_id_label;
    QLabel *label_3;
    QPushButton *search_button;
    QWidget *enroll_1;
    QLabel *en_RGBpic;
    QLabel *en_Dpic;
    QLabel *en_RGB_save;
    QLabel *en_D_save;
    QLabel *en_note;
    QLabel *en_name_label;
    QLabel *en_sno_label;
    QLineEdit *en_name_edit;
    QLineEdit *en_sno_edit;
    QPushButton *en_capturebutton;
    QPushButton *en_homebutton;
    QPushButton *en_exitbutton;
    QLabel *en_group_lable;
    QComboBox *en_groupBox;
    QRadioButton *en_male;
    QRadioButton *en_female;
    QLabel *en_gender_label;
    QComboBox *en_grade;
    QLabel *label;
    QWidget *search_2;
    QTableWidget *tableWidget;
    QComboBox *sr_name;
    QLabel *sr_name_lb;
    QLabel *sr_time_lb;
    QLabel *sr_result_lb;
    QComboBox *sr_result;
    QDateEdit *dateEdit;
    QPushButton *sr_searchButton;
    QPushButton *sr_homebutton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *face_recognitionClass)
    {
        if (face_recognitionClass->objectName().isEmpty())
            face_recognitionClass->setObjectName(QStringLiteral("face_recognitionClass"));
        face_recognitionClass->resize(1034, 641);
        centralWidget = new QWidget(face_recognitionClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 1001, 601));
        home_0 = new QWidget();
        home_0->setObjectName(QStringLiteral("home_0"));
        h_label = new QLabel(home_0);
        h_label->setObjectName(QStringLiteral("h_label"));
        h_label->setGeometry(QRect(170, 30, 551, 81));
        h_RGBpic = new QLabel(home_0);
        h_RGBpic->setObjectName(QStringLiteral("h_RGBpic"));
        h_RGBpic->setGeometry(QRect(20, 120, 261, 361));
        h_Dpic = new QLabel(home_0);
        h_Dpic->setObjectName(QStringLiteral("h_Dpic"));
        h_Dpic->setGeometry(QRect(325, 120, 261, 361));
        verticalLayoutWidget = new QWidget(home_0);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(660, 120, 81, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        h_name = new QLabel(verticalLayoutWidget);
        h_name->setObjectName(QStringLiteral("h_name"));

        verticalLayout->addWidget(h_name);

        h_id = new QLabel(verticalLayoutWidget);
        h_id->setObjectName(QStringLiteral("h_id"));

        verticalLayout->addWidget(h_id);

        h_res = new QLabel(verticalLayoutWidget);
        h_res->setObjectName(QStringLiteral("h_res"));

        verticalLayout->addWidget(h_res);

        enroll_button = new QPushButton(home_0);
        enroll_button->setObjectName(QStringLiteral("enroll_button"));
        enroll_button->setGeometry(QRect(730, 440, 81, 31));
        exit_button = new QPushButton(home_0);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        exit_button->setGeometry(QRect(820, 440, 75, 31));
        h_threshold = new QLabel(home_0);
        h_threshold->setObjectName(QStringLiteral("h_threshold"));
        h_threshold->setGeometry(QRect(760, 530, 31, 22));
        h_th = new QDoubleSpinBox(home_0);
        h_th->setObjectName(QStringLiteral("h_th"));
        h_th->setGeometry(QRect(800, 530, 62, 22));
        h_name_label = new QLabel(home_0);
        h_name_label->setObjectName(QStringLiteral("h_name_label"));
        h_name_label->setGeometry(QRect(760, 140, 151, 41));
        h_id_label = new QLabel(home_0);
        h_id_label->setObjectName(QStringLiteral("h_id_label"));
        h_id_label->setGeometry(QRect(760, 200, 151, 41));
        label_3 = new QLabel(home_0);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(760, 270, 151, 41));
        search_button = new QPushButton(home_0);
        search_button->setObjectName(QStringLiteral("search_button"));
        search_button->setGeometry(QRect(640, 440, 81, 31));
        stackedWidget->addWidget(home_0);
        enroll_1 = new QWidget();
        enroll_1->setObjectName(QStringLiteral("enroll_1"));
        en_RGBpic = new QLabel(enroll_1);
        en_RGBpic->setObjectName(QStringLiteral("en_RGBpic"));
        en_RGBpic->setGeometry(QRect(20, 10, 261, 271));
        en_Dpic = new QLabel(enroll_1);
        en_Dpic->setObjectName(QStringLiteral("en_Dpic"));
        en_Dpic->setGeometry(QRect(310, 10, 261, 271));
        en_RGB_save = new QLabel(enroll_1);
        en_RGB_save->setObjectName(QStringLiteral("en_RGB_save"));
        en_RGB_save->setGeometry(QRect(20, 300, 261, 271));
        en_D_save = new QLabel(enroll_1);
        en_D_save->setObjectName(QStringLiteral("en_D_save"));
        en_D_save->setGeometry(QRect(310, 300, 261, 271));
        en_note = new QLabel(enroll_1);
        en_note->setObjectName(QStringLiteral("en_note"));
        en_note->setGeometry(QRect(600, 70, 281, 151));
        en_name_label = new QLabel(enroll_1);
        en_name_label->setObjectName(QStringLiteral("en_name_label"));
        en_name_label->setGeometry(QRect(600, 270, 54, 31));
        en_sno_label = new QLabel(enroll_1);
        en_sno_label->setObjectName(QStringLiteral("en_sno_label"));
        en_sno_label->setGeometry(QRect(600, 320, 54, 31));
        en_name_edit = new QLineEdit(enroll_1);
        en_name_edit->setObjectName(QStringLiteral("en_name_edit"));
        en_name_edit->setGeometry(QRect(680, 270, 181, 31));
        en_sno_edit = new QLineEdit(enroll_1);
        en_sno_edit->setObjectName(QStringLiteral("en_sno_edit"));
        en_sno_edit->setGeometry(QRect(680, 320, 181, 31));
        en_capturebutton = new QPushButton(enroll_1);
        en_capturebutton->setObjectName(QStringLiteral("en_capturebutton"));
        en_capturebutton->setGeometry(QRect(900, 370, 81, 31));
        en_homebutton = new QPushButton(enroll_1);
        en_homebutton->setObjectName(QStringLiteral("en_homebutton"));
        en_homebutton->setGeometry(QRect(900, 420, 81, 31));
        en_exitbutton = new QPushButton(enroll_1);
        en_exitbutton->setObjectName(QStringLiteral("en_exitbutton"));
        en_exitbutton->setGeometry(QRect(900, 470, 81, 31));
        en_group_lable = new QLabel(enroll_1);
        en_group_lable->setObjectName(QStringLiteral("en_group_lable"));
        en_group_lable->setGeometry(QRect(600, 370, 54, 31));
        en_groupBox = new QComboBox(enroll_1);
        en_groupBox->setObjectName(QStringLiteral("en_groupBox"));
        en_groupBox->setGeometry(QRect(680, 370, 181, 31));
        en_male = new QRadioButton(enroll_1);
        en_male->setObjectName(QStringLiteral("en_male"));
        en_male->setGeometry(QRect(690, 420, 50, 31));
        en_female = new QRadioButton(enroll_1);
        en_female->setObjectName(QStringLiteral("en_female"));
        en_female->setGeometry(QRect(740, 420, 50, 31));
        en_gender_label = new QLabel(enroll_1);
        en_gender_label->setObjectName(QStringLiteral("en_gender_label"));
        en_gender_label->setGeometry(QRect(600, 420, 54, 31));
        en_grade = new QComboBox(enroll_1);
        en_grade->setObjectName(QStringLiteral("en_grade"));
        en_grade->setGeometry(QRect(680, 470, 181, 31));
        label = new QLabel(enroll_1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(600, 470, 54, 31));
        stackedWidget->addWidget(enroll_1);
        search_2 = new QWidget();
        search_2->setObjectName(QStringLiteral("search_2"));
        tableWidget = new QTableWidget(search_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 110, 981, 481));
        sr_name = new QComboBox(search_2);
        sr_name->setObjectName(QStringLiteral("sr_name"));
        sr_name->setGeometry(QRect(80, 30, 69, 31));
        sr_name_lb = new QLabel(search_2);
        sr_name_lb->setObjectName(QStringLiteral("sr_name_lb"));
        sr_name_lb->setGeometry(QRect(30, 31, 54, 31));
        sr_time_lb = new QLabel(search_2);
        sr_time_lb->setObjectName(QStringLiteral("sr_time_lb"));
        sr_time_lb->setGeometry(QRect(240, 31, 54, 31));
        sr_result_lb = new QLabel(search_2);
        sr_result_lb->setObjectName(QStringLiteral("sr_result_lb"));
        sr_result_lb->setGeometry(QRect(450, 31, 54, 31));
        sr_result = new QComboBox(search_2);
        sr_result->setObjectName(QStringLiteral("sr_result"));
        sr_result->setGeometry(QRect(500, 31, 69, 31));
        dateEdit = new QDateEdit(search_2);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(290, 31, 110, 31));
        sr_searchButton = new QPushButton(search_2);
        sr_searchButton->setObjectName(QStringLiteral("sr_searchButton"));
        sr_searchButton->setGeometry(QRect(630, 31, 75, 31));
        sr_homebutton = new QPushButton(search_2);
        sr_homebutton->setObjectName(QStringLiteral("sr_homebutton"));
        sr_homebutton->setGeometry(QRect(710, 31, 75, 31));
        stackedWidget->addWidget(search_2);
        face_recognitionClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(face_recognitionClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        face_recognitionClass->setStatusBar(statusBar);

        retranslateUi(face_recognitionClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(face_recognitionClass);
    } // setupUi

    void retranslateUi(QMainWindow *face_recognitionClass)
    {
        face_recognitionClass->setWindowTitle(QApplication::translate("face_recognitionClass", "face_recognition", Q_NULLPTR));
        h_label->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">BRL RGB_D\344\272\272\350\204\270\350\257\206\345\210\253\347\263\273\347\273\237</span></p></body></html>", Q_NULLPTR));
        h_RGBpic->setText(QApplication::translate("face_recognitionClass", "TextLabel", Q_NULLPTR));
        h_Dpic->setText(QApplication::translate("face_recognitionClass", "TextLabel", Q_NULLPTR));
        h_name->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\345\247\223\345\220\215</span></p></body></html>", Q_NULLPTR));
        h_id->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\345\255\246\345\217\267</span></p></body></html>", Q_NULLPTR));
        h_res->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\347\273\223\346\236\234</span></p></body></html>", Q_NULLPTR));
        enroll_button->setText(QApplication::translate("face_recognitionClass", "\346\263\250 \345\206\214", Q_NULLPTR));
        exit_button->setText(QApplication::translate("face_recognitionClass", "\351\200\200 \345\207\272", Q_NULLPTR));
        h_threshold->setText(QApplication::translate("face_recognitionClass", "\351\230\210 \345\200\274", Q_NULLPTR));
        h_name_label->setText(QString());
        h_id_label->setText(QString());
        label_3->setText(QString());
        search_button->setText(QApplication::translate("face_recognitionClass", "\346\237\245 \350\257\242", Q_NULLPTR));
        en_RGBpic->setText(QApplication::translate("face_recognitionClass", "TextLabel", Q_NULLPTR));
        en_Dpic->setText(QApplication::translate("face_recognitionClass", "TextLabel", Q_NULLPTR));
        en_RGB_save->setText(QApplication::translate("face_recognitionClass", "NO RGB-PICTURE CAPTURED", Q_NULLPTR));
        en_D_save->setText(QApplication::translate("face_recognitionClass", "NO DEPTH-PICTURE CAPTURED", Q_NULLPTR));
        en_note->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p>\346\263\250\346\204\217\357\274\232</p><p>1.\347\202\271\345\207\273\346\213\215\347\205\247\346\214\211\351\222\256\350\216\267\345\217\226\346\263\250\345\206\214\345\233\276\345\203\217\357\274\214\346\230\276\347\244\272\345\234\250\344\270\213\346\226\271\343\200\202</p><p>2.\345\234\250\345\257\271\345\272\224\346\241\206\344\270\255\350\276\223\345\205\245\345\247\223\345\220\215\345\222\214\347\274\226\345\217\267\343\200\202</p><p>3.\345\275\223\347\241\256\350\256\244\346\227\240\350\257\257\345\220\216\347\202\271\345\207\273\346\213\215\347\205\247\346\214\211\351\222\256\345\256\214\346\210\220\346\263\250\345\206\214\343\200\202</p><p>4.\347\202\271\345\207\273\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242\346\214\211\351\222\256\357\274\214\350\277\224\345\233\236\344\270\212\344\270\200\347\225\214\351\235\242\343\200\202</p></body></html>", Q_NULLPTR));
        en_name_label->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\345\247\223\345\220\215</span></p></body></html>", Q_NULLPTR));
        en_sno_label->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\345\255\246\345\217\267</span></p></body></html>", Q_NULLPTR));
        en_capturebutton->setText(QApplication::translate("face_recognitionClass", "\346\213\215 \347\205\247", Q_NULLPTR));
        en_homebutton->setText(QApplication::translate("face_recognitionClass", "\350\277\224\345\233\236\344\270\273\351\241\265\351\235\242", Q_NULLPTR));
        en_exitbutton->setText(QApplication::translate("face_recognitionClass", "\351\200\200 \345\207\272", Q_NULLPTR));
        en_group_lable->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\347\273\204\347\273\207</span></p></body></html>", Q_NULLPTR));
        en_male->setText(QApplication::translate("face_recognitionClass", "\347\224\267", Q_NULLPTR));
        en_female->setText(QApplication::translate("face_recognitionClass", "\345\245\263", Q_NULLPTR));
        en_gender_label->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\346\200\247\345\210\253</span></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\345\271\264\347\272\247</span></p></body></html>", Q_NULLPTR));
        sr_name_lb->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\345\247\223\345\220\215</span></p></body></html>", Q_NULLPTR));
        sr_time_lb->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">time</span></p></body></html>", Q_NULLPTR));
        sr_result_lb->setText(QApplication::translate("face_recognitionClass", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">\347\273\223\346\236\234</span></p></body></html>", Q_NULLPTR));
        sr_searchButton->setText(QApplication::translate("face_recognitionClass", "\346\237\245 \350\257\242", Q_NULLPTR));
        sr_homebutton->setText(QApplication::translate("face_recognitionClass", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class face_recognitionClass: public Ui_face_recognitionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_RECOGNITION_H
