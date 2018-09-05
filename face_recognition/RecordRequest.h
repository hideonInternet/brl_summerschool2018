#include<BaseNet.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qmessagebox.h>
#include <ctime>

using namespace std;

class RecordRequest :public BaseNet{
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
public:
	RecordRequest();
	void getResult(QByteArray, std::function<void(bool, int)>);
	string encrypt();
private:
	std::function<void(bool, int)> checkCallback;

};