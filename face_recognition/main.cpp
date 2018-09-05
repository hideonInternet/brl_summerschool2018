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
	QPixmap pixmap("background.png");//设定图片
	QPalette palette;//创建一个调色板对象
	palette.setBrush(w.backgroundRole(), QBrush(pixmap));
	w.setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联
	w.setMask(pixmap.mask()); //可以将图片中透明部分显示为透明的
	w.setAutoFillBackground(true);
	w.show();
	
	//cout << imgbase64 << endl;
	return a.exec();
}
