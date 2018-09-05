
#include"LivenessReqeust.h"


const QString LIVENESS_DETECT = QString("https://aip.baidubce.com/rest/2.0/face/v3/faceverify?access_token=24.9a85b36525b6c0d910e1bdd302d05f36.2592000.1538359437.282335-11757171");

LivenessRequest::LivenessRequest(){
	httpRequest.setRawHeader("content-type", "application/json;charset=UTF-8");
	QSslConfiguration config;
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::AnyProtocol);
	httpRequest.setSslConfiguration(config);
}

void LivenessRequest::getResult(QByteArray data, std::function<void(bool, float)> callback){
	this->checkCallback = callback;
	post(LIVENESS_DETECT, data);
}

void LivenessRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode){
	qDebug() << data;
	float face_liveness=0;
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
			face_liveness = obj.value("face_liveness").toVariant().toFloat();
		}
		this->checkCallback(true, face_liveness);
	}
	else{
		qDebug() << QStringLiteral("ÍøÂçÎÊÌâ£¬¼ì²âÊ§°Ü");
		QMessageBox::information(NULL, "Error", "Detect Failed:net problem");
		exit(0);
	}
}	