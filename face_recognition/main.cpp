#include "face_recognition.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*QFile f(":qdarkstyle/style.qss");
	if (!f.exists())
	{
		printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
	}*/
	face_recognition w;
	QPixmap pixmap("background.png");//�趨ͼƬ
	QPalette palette;//����һ����ɫ�����
	palette.setBrush(w.backgroundRole(), QBrush(pixmap));
	w.setPalette(palette);//���ô��ڵ�ɫ��Ϊpalette�����ںͻ��������
	w.setMask(pixmap.mask()); //���Խ�ͼƬ��͸��������ʾΪ͸����
	w.setAutoFillBackground(true);
	w.show();
	
	//cout << imgbase64 << endl;
	return a.exec();
}
