#include"RecordRequest.h"

const QString ADD_RECORD = QString("http://onclick.ac.cn:8080/api/add_record/");
RecordRequest::RecordRequest(){}

void RecordRequest::getResult(QByteArray data, std::function<void(bool, int)> callback){
	this->checkCallback = callback;
	post(ADD_RECORD, data);
}

void RecordRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode){
	qDebug() << data;
	if (statusCode == 200){
		//解析json
		QJsonParseError jsonError;
		QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);

		if (jsonError.error != QJsonParseError::NoError) {
			qDebug() << QStringLiteral("解析Json失败");
			QMessageBox::information(NULL, "Error", "Parse Failed");
			exit(0);
		}
		QJsonObject obj = document.object();
		int errnum_tmp = obj.value("errnum").toVariant().toInt();
		if (errnum_tmp != 0){
			qDebug() << QStringLiteral("打卡失败");
			QString msg = obj.value("msg").toString();
			QMessageBox::information(NULL, "Error", "Failed to record:"+msg);
			this->checkCallback(false, errnum_tmp);
		}
		else{
			qDebug() << "record success";
			this->checkCallback(true, errnum_tmp);
		}

	}
	else{
		qDebug() << QStringLiteral("打卡失败，网络问题");
		QMessageBox::information(NULL, "Error", "net");
		exit(0);
	}
}

string RecordRequest::encrypt(){
	//加密表
	int code[10][10] = { { 13, 7, 4, 11, 5, 9, 12, 6, 5, 13 },
	{ 5, 8, 9, 7, 9, 13, 12, 3, 8, 14 },
	{ 6, 12, 6, 14, 13, 13, 8, 13, 12, 7 },
	{ 9, 5, 10, 12, 8, 8, 4, 11, 9, 7 },
	{ 11, 6, 9, 13, 9, 9, 11, 7, 5, 11 },
	{ 5, 8, 12, 10, 9, 7, 4, 9, 4, 4, },
	{ 5, 9, 12, 13, 10, 7, 8, 11, 6, 4 },
	{ 12, 8, 6, 12, 8, 9, 9, 8, 6, 12 },
	{ 18, 13, 4, 8, 12, 5, 13, 4, 12, 11 },
	{ 11, 7, 6, 7, 9, 8, 12, 11, 4, 8 }
	};
	int code2[10][10] = { { 1, 5, 7, 3, 11, 29, 19, 4, 5, 22 },
	{ 5, 18, 19, 27, 3, 7, 2, 3, 8, 21 },
	{ 3, 7, 8, 31, 14, 6, 24, 17, 11, 6 },
	{ 59, 35, 13, 11, 28, 3, 1, 4, 38, 2 },
	{ 13, 14, 19, 13, 25, 19, 27, 2, 34, 17 },
	{ 71, 22, 11, 19, 27, 6, 4, 9, 4, 4, },
	{ 85, 3, 19, 31, 10, 7, 21, 11, 6, 4 },
	{ 2, 8, 6, 12, 8, 9, 9, 8, 6, 12 },
	{ 13, 13, 4, 8, 54, 15, 1, 4, 12, 11 },
	{ 11, 37, 46, 57, 19, 8, 12, 33, 23, 17 }
	};
	int code3[10][10] = { { 5, 23, 6, 22, 14, 21, 13, 12, 28, 21 },
	{ 40, 5, 22, 23, 31, 3, 20, 18, 16, 34 },
	{ 16, 12, 1, 10, 18, 17, 13, 41, 37, 25 },
	{ 27, 23, 16, 14, 26, 17, 21, 21, 2, 10 },
	{ 9, 8, 10, 14, 8, 9, 21, 25, 6, 11 },
	{ 30, 21, 44, 10, 9, 7, 7, 9, 10, 16, },
	{ 14, 27, 5, 13, 18, 7, 8, 11, 6, 4 },
	{ 12, 8, 6, 33, 25, 21, 29, 8, 7, 12 },
	{ 18, 29, 4, 13, 12, 14, 13, 17, 12, 41 },
	{ 11, 19, 6, 13, 8, 8, 12, 23, 5, 26 }
	};

	std::time_t t = std::time(0);  // t is an integer type
	//cout << t << endl;
	//cin >> t;
	int _t = t;//时间戳
	int k = 0;
	char encrypt_str[21];
	string str = to_string(_t);

	//将时间转换为数组形式
	char *c = (char*)str.c_str();
	int res_tmp[10];
	int step = (255 - 16);
	//转为时间数组
	for (int i = 0; i < 10; i++){
		res_tmp[i] = c[i] - '0';
	}
	//存储结果数组
	int res[10];
	//std::cout << _t << " seconds since 01-Jan-1970\n";
	int _c2 = code[res_tmp[9]][res_tmp[8]];
	int _c3 = code2[_c2 % 10][res_tmp[7]];
	for (int i = 0; i < 10; i++){
		/*
		+1：是为了防止有0产生，在左移后还是为0
		算法思想就是根据最后一位选择code的哪一行
		*/
		res[i] = (res_tmp[i] + 1 << code3[_c3 % 10][i]);
		//为了保证得到的数字大小范围在17~255之间，这样在转换为16进制的时候，可以保证一定有两位数
		res[i] = 17 + res[i] % step;
		res[i] = res[i]>0 ? res[i] : -res[i];
		//cout <<"res[i] is: " <<res[i] << endl;
		char buffer[3];
		//进制转换
		_itoa_s(res[i], buffer, 16);
		encrypt_str[k++] = buffer[0];
		encrypt_str[k++] = buffer[1];
		//cout << "k is " << k << endl;
	}
	encrypt_str[k] = '\0';
	//string final_str = encrypt_str;
	return encrypt_str;
}