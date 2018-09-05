#ifndef FACE_RECOGNITION_H
#define FACE_RECOGNITION_H

#include <QtWidgets/QMainWindow>
#include<qpalette.h>
#include "FaceRecognition.h"
#include "FeatureGroup.h"
#include "InitialGUIRequest.h"
#include"RecordRequest.h"
#include"EnrollRequest.h"
#include"LivenessReqeust.h"
#include <QApplication>
#include <QtGui>
#include "ui_face_recognition.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTime>
#include <qmessagebox.h>
#include <qtimer.h>
#include "Base64.h"
#include <time.h>
#include <librealsense/rs.hpp>
struct Record
{
	std::string name;
	std::string sno;
	std::string date;
	std::string result;
};

using namespace cv;
using namespace std;

class face_recognition : public QMainWindow
{
	Q_OBJECT

public:
	face_recognition(QWidget *parent = 0);
	void enrollRequest();
	void myRemoveRow();
	void initialGUI();
	void setRecord(string name,string id,string res);
	void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
	vector<Record> getRecord();
	Ui::face_recognitionClass getUi();
	~face_recognition();
private:
	Ui::face_recognitionClass ui;

	map<string, int> _groupMap;
	Feature f;
	initialGUIRequest *i;
	FaceRecognition fr;
	EnrollRequest *e;
	RecordRequest *r;
	LivenessRequest *l;
	rs::context ctx;
	rs::device &dev = *ctx.get_device(0);
	QTimer *timer_camera;//rs����ʱ�����
	QTimer *timer_rec;//�����������ʱ�����

	int v_i_change = 0;//״̬ת����һ��0 1����״̬
	bool rs_in = 0;//�ж�����ͷ�Ƿ��
	Mat figure_gr;//�洢RGB galleryͼ��
	Mat figure_gd;//�洢depth galleryͼ��

	QString ID_num;//ʶ���
	QString name;//ע������


	private slots:
	//��Ҫ��������¼
	void search();
	//-----------------realsense-------------//
	void rsopen();
	void rstime_on();
	void rstime_off();
	//-----------------����ת��---------------//
	void setStackCurrentPage(quint8 index);
	void click_enroll_on();
	void click_home_on();
	void click_search_on();
	//-----------------register--------------------//
	//void RGB_D_save_info();//void iden_save_info();
	void RGB_D_img_capture();
	void recognition();

	

};

#endif // FACE_RECOGNITION_H
