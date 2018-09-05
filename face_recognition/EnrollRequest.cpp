#include"EnrollRequest.h"

const QString ADD_EMPLOYEE = QString("http://onclick.ac.cn:8080/api/add_employee/");
EnrollRequest::EnrollRequest(){}

void EnrollRequest::getResult(QByteArray data,std::function<void(bool, int)> callback){
	this->checkCallback = callback;
	post(ADD_EMPLOYEE, data);
}

void EnrollRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode){
	int id;
	qDebug() << data;
	if (statusCode == 200){
		//½âÎöjson
		QJsonParseError jsonError;
		QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);

		if (jsonError.error != QJsonParseError::NoError) {
			qDebug() << QStringLiteral("½âÎöJsonÊ§°Ü");
			QMessageBox::information(NULL, "Error", "Initial Failed");
			exit(0);
		}
		if (document.isObject()){
			QJsonObject obj = document.object();
			int errnum_tmp = obj.value("errnum").toVariant().toInt();
			if (errnum_tmp == 1){
				qDebug() << QStringLiteral("×¢²áÊ§°Ü");
				QMessageBox::information(NULL, "Error", "Enroll Failed");
				exit(0);
			}
			else{
				id = obj.value("id").toVariant().toInt();
			}
			this->checkCallback(true, id);
		}
	} else{
		qDebug() << QStringLiteral("ÍøÂçÎÊÌâ£¬×¢²áÊ§°Ü");
		QMessageBox::information(NULL, "Error", "Enroll Failed:net problem");
		exit(0);
	}
}