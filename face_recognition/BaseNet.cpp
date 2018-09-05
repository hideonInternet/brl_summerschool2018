#include"BaseNet.h"

BaseNet::BaseNet()
{
	httpRequest.setRawHeader("Accept-Language", "zh-CN,zh;q=0.8");
	httpRequest.setRawHeader("Connection", "keep-alive");
	httpRequest.setRawHeader("content-type", "application/x-www-form-urlencoded;charset=utf-8");
	httpRequest.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36");
	httpRequest.setRawHeader("Upgrade-Insecure-Requests", "1");
	httpRequest.setRawHeader("Host", "118.24.127.131:8080");

	/*settings = new QSettings("XXX");
	QString id = settings->value(SETTING_ACCOUNT_ID, "").toString();
	QString token = settings->value(SETTING_ACCOUNT_TOKEN, "").toString();

	if (!id.isEmpty()) {
		httpRequest.setRawHeader("X-XXX-User-ID", id.toStdString().c_str());
	}

	if (!token.isEmpty()) {
		httpRequest.setRawHeader("X-XXX-User-Token", token.toStdString().c_str());
	}

	qDebug() << "BaseNet...id:" << id << " token:" + token;*/
	QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

BaseNet::~BaseNet()
{
	networkAccessManager.disconnect();

}

void BaseNet::get(const QString url)
{
	httpRequest.setUrl(QUrl(url));
	networkAccessManager.get(httpRequest);
}

void BaseNet::post(const QString url, const QByteArray &data)
{
	httpRequest.setUrl(QUrl(url));
	networkAccessManager.post(httpRequest, data);
}

void BaseNet::serviceRequestFinished(QNetworkReply *reply)
{
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	qDebug() << "BaseNet...serviceRequestFinished...statusCode:" << statusCode;
	QByteArray data = reply->readAll();
	qDebug() << data;
	if (reply->error() == QNetworkReply::NoError) {
		requestFinished(reply, data, statusCode);
	}
	else {
		requestFinished(reply, "", statusCode);
	}

	// At the end of that slot, we won't need it anymore
	reply->deleteLater();
}
