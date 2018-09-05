#include"BaseNet.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qmessagebox.h>

using namespace std;

class LivenessRequest :public BaseNet{

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

public:
	LivenessRequest();
	void getResult(QByteArray, std::function<void(bool, float)>);
private:
	std::function<void(bool, float)> checkCallback;
};