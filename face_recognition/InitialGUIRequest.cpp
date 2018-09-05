#include"InitialGUIRequest.h"

const QString GET_GRUOP = QString("http://onclick.ac.cn:8080/api/return_group/");

initialGUIRequest::initialGUIRequest(){
}
void initialGUIRequest::getGroupList(std::function<void(bool, map<string,int>)> callback){
	this->checkCallback = callback;
	get(GET_GRUOP);
}
void initialGUIRequest::requestFinished(QNetworkReply* reply, const QByteArray bytes, const int statusCode){
	map<string, int> groupMap;
	if (statusCode == 200){
		//½âÎöjson
		QJsonParseError jsonError;
		QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);
		if (jsonError.error != QJsonParseError::NoError) {
			qDebug() << QStringLiteral("½âÎöJsonÊ§°Ü");
			QMessageBox::information(NULL, "Error", "Initial Failed");
			exit(0);
		}
		// ½âÎöJson
		if (document.isObject()) {
			QJsonObject obj = document.object();
			string name;
			int id;
			QJsonValue group_data = obj.value("group_data");
			if (group_data.isArray()) { 
				QJsonArray array = group_data.toArray();
				for (int i = 0; i < array.size(); ++i) {
					QJsonObject value = array.at(i).toObject();
					QJsonValue tmp_name = value.value("name");
					QJsonValue tmp_id = value.value("id");
					if (tmp_name.isString()){
						name = tmp_name.toString().toStdString();
					}
					if (tmp_id.isDouble()){
						id = tmp_id.toVariant().toInt();
					}
					
					groupMap.insert(std::pair<string, int>(name, id));
				}
				this->checkCallback(true, groupMap);
			}
		}
	} else{
		this->checkCallback(false, groupMap);
	}
}