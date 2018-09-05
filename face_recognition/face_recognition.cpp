#include "face_recognition.h"



face_recognition::face_recognition(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer_camera = new QTimer(this);
	timer_rec = new QTimer(this);
	
	//--------------ui初始化---------------//
	initialGUI();
	
	
	rs::log_to_console(rs::log_severity::warn);
	if (ctx.get_device_count() == 0) throw std::runtime_error("No device detected. Is it plugged in?");
	dev.enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 60);
	dev.enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 60);
	dev.start();

	connect(timer_camera, SIGNAL(timeout()), this, SLOT(rsopen()));//不断更新摄像头
	connect(timer_rec, SIGNAL(timeout()), this, SLOT(recognition()));//不断进行检测
	
	timer_rec->start(3000);
	timer_camera->start(1000 / 24);
	//--------------槽函数---------------------------//
	//-----------------home_0界面--------------------//
	//connect(ui.en_enrollbutton, SIGNAL(clicked()), this, SLOT(rstime_off()));
	connect(ui.enroll_button,SIGNAL(clicked()),this,SLOT(click_enroll_on()));//转到注册界面
	connect(ui.exit_button, SIGNAL(clicked()), this, SLOT(close()));//退出系统
	//-----------------enroll_1界面-------------------//
	connect(ui.en_exitbutton, SIGNAL(clicked()), this, SLOT(close()));//退出系统
	connect(ui.en_capturebutton, SIGNAL(clicked()), this, SLOT(RGB_D_img_capture()));
	//connect(ui.en_homebutton, SIGNAL(clicked()), this, SLOT(rstime_off()));
	connect(ui.en_homebutton, SIGNAL(clicked()), this, SLOT(click_home_on()));
	//-----------------search_2界面-----------------------//
	connect(ui.search_button, SIGNAL(clicked()), this, SLOT(click_search_on()));
	connect(ui.sr_searchButton, SIGNAL(clicked()), this, SLOT(search()));
	connect(ui.sr_homebutton, SIGNAL(clicked()), this, SLOT(click_home_on()));
}

face_recognition::~face_recognition()
{
	
	
}

void face_recognition::rsopen(){
	dev.wait_for_frames();
	uchar* pRgb = (uchar*)dev.get_frame_data(rs::stream::color);
	//uint16_t *depthImage = (uint16_t *)dev.get_frame_data(rs::stream::depth);
	//depth_aligened_to_color会出错，不知道会不会影响检测
	uint16_t* pCad = (uint16_t*)dev.get_frame_data(rs::stream::depth_aligned_to_color);
	Mat color(480, 640, CV_8UC3, pRgb);//color:从realsense获取的RGB图像
	Mat depth(480, 640, CV_16UC1, pCad);//depth:从realsense获取的depth图像
	for (int y = 0; y<480; y++)
	{
		ushort* p = depth.ptr<ushort>(y);
		for (int x = 0; x<640; x++)
		{
			ushort d = depth.at<ushort>(y, x);
			p[x] = d;
			//距离在0.2m至1.2m之间
			if (d > 10000)
			{
				p[x] = 0.0255*(d - 10000);
				//if (d > 20000){
				//	p[x] = 255;
				//	//QMessageBox::information(NULL, "Information", "Be close to the camera!!");
				//}
			}
			else{
				p[x] = 0;
			}
		}
	}
	cv::Mat frame, frame_RGB;
	frame = color.clone();
	Mat figure;//librealsense图像转换为RGB后存放（和SDK不同）
	cv::cvtColor(frame, figure, cv::COLOR_BGR2RGB);
	cv::resize(frame, frame_RGB, cv::Size(320, 240));

	
	//实时展示人脸框
	//fr.showFace(frame_RGB);
	//-------------------设置GRB图片显示-------------//
	QImage ColorImage = QImage((const uchar*)frame_RGB.data, frame_RGB.cols, frame_RGB.rows, frame_RGB.cols*frame_RGB.channels(), QImage::Format_RGB888);
	if (v_i_change == 0){
		ColorImage.scaled(ui.h_RGBpic->size(), Qt::KeepAspectRatio);
		ui.h_RGBpic->setPixmap(QPixmap::fromImage(ColorImage));
	}
	if (v_i_change == 1){
		ColorImage.scaled(ui.en_RGBpic->size(), Qt::KeepAspectRatio);
		ui.en_RGBpic->setPixmap(QPixmap::fromImage(ColorImage));
		figure_gr = figure;//用于注册界面
	}
	//--------------------设置depth图片显示--------------------//
	Mat depth1;
	depth.convertTo(depth1, CV_8UC1, 1);
	cv::resize(depth1, depth1, cv::Size(320, 240));
	QImage DepthImage = QImage((const uchar*)depth1.data, depth1.cols, depth1.rows, depth1.cols*depth1.channels(), QImage::Format_Grayscale8);

	if (v_i_change == 0){
		DepthImage.scaled(ui.h_Dpic->size(), Qt::KeepAspectRatio);
		ui.h_Dpic->setPixmap(QPixmap::fromImage(DepthImage));
	}
	if (v_i_change == 1){
		DepthImage.scaled(ui.en_Dpic->size(), Qt::KeepAspectRatio);
		ui.en_Dpic->setPixmap(QPixmap::fromImage(DepthImage));
		figure_gd = depth;
	}
}

//------------------------初始化ui------------------------//
void face_recognition::initialGUI(){
		//
		int c=this->ctx.get_device_count();
		if (c == 0){
			QMessageBox::information(NULL, "Error", "No Camera");
			exit(0);
		}
		//设置日期
		ui.dateEdit->setDisplayFormat("yyyy/MM/dd");
		ui.dateEdit->setDateTime(QDateTime::currentDateTime());
		//设置人员
		vector<Record> v_r=getRecord();
		vector<Record>::iterator it = v_r.begin();
		ui.sr_name->addItem(QString::fromStdString("All"), QVariant(tr("1")));
		while (it != v_r.end() && v_r.size()>0){
			qDebug() << v_r.size();
			qDebug() << QString::fromStdString(it->name);
			if (ui.sr_name->findText(QString::fromStdString(it->name)) == -1){
				ui.sr_name->addItem(QString::fromStdString(it->name), QVariant(tr((it->name).c_str())));
			}
			it++;
		}
		//设置结果combobox
		ui.sr_result->addItem(QString::fromStdString("All"), QVariant(tr("1")));
		ui.sr_result->addItem(QString::fromStdString("Accept"), QVariant(tr("Accept")));
		ui.sr_result->addItem(QString::fromStdString("Reject"), QVariant(tr("Reject")));
		ui.sr_result->addItem(QString::fromStdString("Error"), QVariant(tr("Error")));
		//设置tablewidget
		ui.tableWidget->setColumnCount(3);
		QStringList header;
		header << tr("name") << tr(" time") << tr("result");
		ui.tableWidget->setHorizontalHeaderLabels(header);
		QFont font;
		font.setBold(true);
		ui.tableWidget->horizontalHeader()->setFont(font);
		ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
		ui.tableWidget->verticalHeader()->setDefaultSectionSize(15); //设置行高
		ui.tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
		ui.tableWidget->setShowGrid(false); //设置不显示格子线
		ui.tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
		ui.tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//可多选
		ui.tableWidget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
		ui.tableWidget->horizontalHeader()->setHighlightSections(false);
		
		//初始化阈值
		ui.h_th->setValue(0.6);
		ui.h_th->setRange(0, 1);
		ui.h_th->setDecimals(2);
		ui.h_th->setSingleStep(0.05);
		ui.en_male->setChecked(true);
		this->setFixedSize(this->width(), this->height());
		this->setWindowIcon(QIcon("icon.png"));
		//初始化GroupComboBox
		i=new initialGUIRequest();
		i->getGroupList([&](bool success, map<string, int> groupMap){
			if (success){
				map<string, int>::iterator it;
				it = groupMap.begin();
				while (it != groupMap.end()){
					_groupMap.insert(pair<string, int>(it->first, it->second));
					ui.en_groupBox->addItem(QString::fromStdString(it->first));
					it++;
				}
			}
			//delete i;
		});
		
		//初始化年级
		QDate date=QDate::currentDate();
		int currentYear=date.year();
		for (int i = 1990; i <= currentYear; i++){
			ui.en_grade->addItem(QString::number(i,10));
		}
}
//发送注册请求
void face_recognition::enrollRequest(){
	QByteArray data;
	string name = ui.en_name_edit->text().toStdString();//
	string sno = ui.en_sno_edit->text().toStdString();//
	string group_name = ui.en_groupBox->currentText().toStdString();
	int group_id_tmp = _groupMap.at(group_name);//
	string group_id = to_string(group_id_tmp);
	string gender = ui.en_male->isChecked() ? "0" : "1";//
	string grade = ui.en_grade->currentText().toStdString();//

	data.append(("sno=" + sno + "&").c_str());
	data.append(("name=" + name + "&").c_str());
	data.append(("group=" + group_id + "&").c_str());
	data.append(("sex=" + gender + "&").c_str());
	data.append(("grade=" + grade).c_str());
	e = new EnrollRequest();
	e->getResult(data, ([&](bool success, int id){
		if (success){
			QString name = ui.en_name_edit->text();
			string name_i = name.toStdString();
			QString sno = ui.en_sno_edit->text();
			string sno_i = sno.toStdString();
			FeatureGroup fg(fr.GetFeatureDims(), &fr);
			float* feat = fr.NewFeatureBuffer();
			fr.GetFeature(figure_gr, feat);
			cv::imwrite("database/pic/" + sno_i + ".jpg", figure_gr);
			fg.AddFeature(feat, name_i, to_string(id), sno_i);
			fg.SaveModel("database/feat.index");
			QMessageBox::information(NULL, "Information", "enroll success");
			ui.en_D_save->clear();
			ui.en_RGB_save->clear();
			//delete e;
		}
	}));
}

//-----------人脸识别-------------------//
void face_recognition::recognition(){
	QByteArray data;
	QByteArray data_liveness;
	QPalette palette;
	dev.wait_for_frames();
	r = new RecordRequest();
	l = new LivenessRequest();
	uchar* pRgb = (uchar*)dev.get_frame_data(rs::stream::color);
	Mat color(480, 640, CV_8UC3, pRgb);//color:从realsense获取的RGB图像
	cv::Mat frame;
	frame = color.clone();
	Mat figure;//librealsense图像转换为RGB后存放（和SDK不同）
	FeatureGroup fg("database/feat.index", &fr);
	cv::cvtColor(frame, figure, cv::COLOR_BGR2RGB);
	
	if (v_i_change == 0 && fr.hasFaceDetected(figure)){
		timer_rec->stop();
		float* feat = fr.NewFeatureBuffer();
		ui.statusBar->showMessage(tr("Face has been detected,Processing....."), 3000);
		fr.GetFeature(figure, feat);
		if (fg.recognition(feat,f,ui.h_th->value())){
		//	Mat im = imread("front.jpg");
		////	data.append(("token=" + r->encrypt()).c_str());
		//	vector<uchar> vecImg;                               //Mat 图片数据转换为vector<uchar>
		//	vector<int> vecCompression_params;
		//	vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		//	vecCompression_params.push_back(90);
		//	imencode(".jpg", im, vecImg, vecCompression_params);
		//	qDebug() << "vecImg'sizeL:";
		//	qDebug() << vecImg.size();
		//	ZBase64 base64;
		//	string imgbase64 = base64.Encode(vecImg.data(), vecImg.size());     //实现图片的base64编码
		//	qDebug() << imgbase64.size();
		//	data_liveness.append(("image=" + base64.urlencode(imgbase64)).c_str());
		//	data_liveness.append("image_type=BASE64");
		//	l->getResult(data, ([&](bool success, float face_liveness){
		//		if (success){
					/*qDebug() << QString::fromStdString("l->getResult()---face_liveness");
					qDebug() << face_liveness;
					if (face_liveness > 0.5){*/
						string id = f.id;
						data.append(("employee=" + id).c_str());
						r->getResult(data, ([&](bool success, int errnum){
							qDebug() << f.name.c_str();
							qDebug() << f.sno.c_str();
							QPalette _palette;
							if (success){
								ui.h_name_label->setText(QString(f.name.c_str()));
								ui.h_id_label->setText(QString(f.sno.c_str()));
								_palette.setColor(QPalette::Window, Qt::green);
								ui.label_3->setPalette(_palette);
								ui.label_3->setAutoFillBackground(true);
								ui.label_3->setText("Accept");
								setRecord(f.name, f.sno, "Accept");
							}
							else{
								ui.h_name_label->clear();
								ui.h_id_label->clear();
								ui.label_3->clear();
								//_palette.setColor(QPalette::Window, this->palette);
								ui.label_3->setPalette(ui.h_res->palette());
								ui.label_3->setAutoFillBackground(true);
								setRecord(f.name, f.sno, "Error");
							}
							timer_rec->start(3000);
						}));//record end
					}
			//}));//liveness detect end;
		else{
			ui.h_name_label->clear();
			ui.h_id_label->clear();
			palette.setColor(QPalette::Background, Qt::red);
			ui.label_3->setPalette(palette);
			ui.label_3->setAutoFillBackground(true);
			ui.label_3->setText("Reject");

			setRecord("unkown", "-1", "Reject");
			timer_rec->start(3000);
		}
		delete feat;
	}
	
}
//------------------界面转换-------------------------//
void face_recognition::setStackCurrentPage(quint8 index)
{
	QWidget *widget = ui.stackedWidget->widget(index);
	ui.stackedWidget->setCurrentWidget(widget);
}

void face_recognition::click_enroll_on(){
	this->setStackCurrentPage(1);
	v_i_change = 1;
}

void face_recognition::click_home_on(){
	this->setStackCurrentPage(0);
	v_i_change = 0;
	myRemoveRow();
	ui.label_3->setPalette(ui.h_res->palette());
	ui.label_3->setAutoFillBackground(true);
	ui.en_sno_edit->clear();
	ui.en_name_edit->clear();
	ui.en_Dpic->clear();
	ui.en_D_save->clear();
	ui.en_RGBpic->clear();
	ui.en_RGB_save->clear();
}

void face_recognition::rstime_on(){
	ui.h_RGBpic->clear();
	ui.h_Dpic->clear();
	rs::log_to_console(rs::log_severity::warn);
	if (ctx.get_device_count() == 0) throw std::runtime_error("No device detected. Is i t plugged in?");
	dev.enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 60);
	dev.enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 60);
	dev.start();
	timer_camera->start(1000 / 24);
}

void face_recognition::click_search_on(){
	setStackCurrentPage(2);
	//设置人员
	ui.sr_name->clear();
	vector<Record> v_r = getRecord();
	vector<Record>::iterator it = v_r.begin();
	ui.sr_name->addItem(QString::fromStdString("All"), QVariant(tr("1")));
	while (it != v_r.end() && v_r.size()>0){
		qDebug() << v_r.size();
		qDebug() << QString::fromStdString(it->name);
		if (ui.sr_name->findText(QString::fromStdString(it->name)) == -1){
			ui.sr_name->addItem(QString::fromStdString(it->name), QVariant(tr((it->name).c_str())));
		}
		it++;
	}
	ui.h_name_label->clear();
	ui.h_id_label->clear();
	ui.label_3->clear();
	v_i_change = 2;
}

void face_recognition::rstime_off(){
	if (v_i_change == 0){
		timer_camera->stop();
		dev.stop();
		ui.h_RGBpic->clear();
		ui.h_Dpic->clear();
		ui.h_name_label->clear();
		ui.h_id_label->clear();
		ui.label_3->clear();
	}
	if (v_i_change == 1){
		timer_camera->stop();
		dev.stop();
		
	}
}
void face_recognition::myRemoveRow(){
	int rowCount = ui.tableWidget->rowCount();
	for (int i = 0; i < rowCount; i++){
		ui.tableWidget->removeRow(0);
	}
}
void face_recognition::search(){
	myRemoveRow();
	QString name=ui.sr_name->currentData().toString();
	QString date = ui.dateEdit->text();
	QString result = ui.sr_result->currentData().toString();
	vector<Record> v_r = getRecord();
	//根据要求筛选vector
	vector<Record> v_res;
	if (name.toStdString()=="1" && result.toStdString()=="1"){
		qDebug() << "1 1";
		vector<Record>::iterator it = v_r.begin();
		while (it != v_r.end()){
			vector<string> v_tmp;
			SplitString(it->date, v_tmp, "_");
			if (v_tmp.at(0) == date.toStdString()){
				v_res.push_back(*it);
			}
			it++;
		}
	}
	if (name.toStdString() != "1" && result.toStdString() == "1"){
		qDebug() << "! 1";
		vector<Record>::iterator it = v_r.begin();
		while (it != v_r.end()){
			vector<string> v_tmp;
			SplitString(it->date, v_tmp, "_");
			if (v_tmp.at(0) == date.toStdString() && it->name==name.toStdString()){
				v_res.push_back(*it);
			}
			it++;
		}
	}
	if (name.toStdString() == "1" && result.toStdString() != "1"){
		qDebug() << "1 !";
		vector<Record>::iterator it = v_r.begin();
		while (it != v_r.end()){
			vector<string> v_tmp;
			SplitString(it->date, v_tmp, "_");
			if (v_tmp.at(0) == date.toStdString() && it->result == result.toStdString()){
				v_res.push_back(*it);
			}
			it++;
		}
	}
	if (name.toStdString() != "1" && result.toStdString() != "1"){
		qDebug() << "! !";
		vector<Record>::iterator it = v_r.begin();
		while (it != v_r.end()){
			vector<string> v_tmp;
			SplitString(it->date, v_tmp, "_");
			if (v_tmp.at(0) == date.toStdString() && it->result == result.toStdString() && it->name == name.toStdString()){
				v_res.push_back(*it);
			}
			it++;
		}
	}
	for (int i = 0; i < v_res.size(); i++){
		int row_count = ui.tableWidget->rowCount(); //获取表单行数
		ui.tableWidget->insertRow(row_count); //插入新行

		QTableWidgetItem *item = new QTableWidgetItem();
		QTableWidgetItem *item1 = new QTableWidgetItem();
		QTableWidgetItem *item2 = new QTableWidgetItem();

		item->setText(QString::fromStdString(v_res.at(i).name));
		item1->setText(QString::fromStdString(v_res.at(i).date));
		item2->setText(QString::fromStdString(v_res.at(i).result));

		ui.tableWidget->setItem(row_count, 0, item);
		ui.tableWidget->setItem(row_count, 1, item1);
		ui.tableWidget->setItem(row_count, 2, item2);

		QColor color("balck");
		item1->setTextColor(color);
		item2->setTextColor(color);
		item->setTextColor(color);
	}
	
}
void face_recognition::setRecord(string name, string sno, string res){
	ofstream file;
	qDebug() << ">>>>>>>>>>>>>>>>>";
	qDebug()<< QString::fromStdString(name);
	file.open("database/record.brl", ios::app);
	QDateTime date = QDateTime::currentDateTime();
	file << name << " "<<sno<<" ";
	file << date.toString("yyyy/MM/dd_HH:mm:ss").toStdString() << " " << res<<endl;
	file.close();
}
vector<Record> face_recognition::getRecord(){
	ifstream file;
	file.open("database/record.brl");
	string tmp_str;
	vector<string> v;
	vector<Record> v_r;
	while (getline(file, tmp_str, '\n')){
		SplitString(tmp_str, v, " ");
	}
	vector<string>::iterator it;

	it=v.begin();
	while (it != v.end()){
		Record tmp_r;
		tmp_r.name = *it;
		it++;
		tmp_r.sno = *it;
		it++;
		tmp_r.date = *it;
		it++;
		tmp_r.result = *it;
		it++;
		v_r.push_back(tmp_r);
	}
	return v_r;
}
void face_recognition::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));

}


//-----------------------------人脸捕获---------------//
void face_recognition::RGB_D_img_capture(){
	if (ui.en_name_edit->text().toStdString() !=""  &&
		ui.en_sno_edit->text().toStdString() !="") { 
		Mat feature_rgb, feature_depth;
		std::vector<seeta::FaceInfo> faces;
		std::vector<seeta::FaceInfo> faces_gd;
		bool flag = fr.hasFaceDetected(figure_gr, faces);
		if (!flag){
			QMessageBox::information(NULL, "Information", "Can not detect the face,and click capture again");
			ui.en_D_save->clear();
			ui.en_RGB_save->clear();
		}
		else if (faces.size()> 1){
			QMessageBox::information(NULL, "Warning", "Only one person permitted");
			ui.en_D_save->clear();
			ui.en_RGB_save->clear();
		}
		else{
		//展示捕获图片
		cv::Mat frame, frame_RGB;
		cv::resize(figure_gr, frame, cv::Size(320, 240));
		cv::cvtColor(frame, frame_RGB, cv::COLOR_BGR2RGB);
		QImage ColorImage = QImage((const uchar*)frame_RGB.data, frame_RGB.cols, frame_RGB.rows, frame_RGB.cols*frame_RGB.channels(), QImage::Format_RGB888);
		ColorImage.scaled(ui.en_RGB_save->size(), Qt::KeepAspectRatio);
		ui.en_RGB_save->setPixmap(QPixmap::fromImage(ColorImage));
		Mat depth1;
		figure_gd.convertTo(depth1, CV_8UC1);
		cv::resize(depth1, depth1, cv::Size(320, 240));
		QImage DepthImage = QImage((const uchar*)depth1.data, depth1.cols, depth1.rows, depth1.cols*depth1.channels(), QImage::Format_Grayscale8);
		DepthImage.scaled(ui.en_D_save->size(), Qt::KeepAspectRatio);
		ui.en_D_save->setPixmap(QPixmap::fromImage(DepthImage));
		/*
		存储特征(暂时是保存rgb)
		*/
		enrollRequest();
		
		}
	}
	else{
		QMessageBox::information(NULL, "Warning", "Please input your name and id");
	}

	}

