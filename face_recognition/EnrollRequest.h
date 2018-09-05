#include"BaseNet.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qmessagebox.h>

using namespace std;

class EnrollRequest:public BaseNet{

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

public:
	EnrollRequest();
	void getResult(QByteArray,std::function<void(bool, int)>);
private:
	std::function<void(bool,int)> checkCallback;
};