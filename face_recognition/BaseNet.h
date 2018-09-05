#pragma once
#include <QNetworkReply>
#include <QNetworkRequest>
#include<iostream>
#include <QSettings>
#include <QSsl>
#include <QSslConfiguration>
#include <QSslSocket>

class BaseNet : public QObject
{
	Q_OBJECT

public:
	BaseNet();
	~BaseNet();
	void get(const QString url);
	void post(const QString url, const QByteArray &data);
	QNetworkRequest httpRequest;

protected:
	virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;
	public slots:
	void serviceRequestFinished(QNetworkReply *reply);

private:
	QNetworkAccessManager networkAccessManager;
	QSettings *settings;
};
