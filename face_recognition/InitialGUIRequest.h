#include"BaseNet.h"
#include<iostream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qmessagebox.h>

using namespace std;

class initialGUIRequest :public BaseNet{

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
public:
	initialGUIRequest();
	void getGroupList(std::function<void(bool, map<string, int>)> callback);
	//map<string, int> groupMap;
private:
	std::function<void(bool, map<string, int>)> checkCallback;
};