#include "MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QFile f(":/qdarkstyle/style.qss");
	if (!f.exists())
	{
		qWarning() << "Unable to set stylesheet, file not found.";
	}
	else
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		a.setStyleSheet(ts.readAll());
	}

	CuteHost::MainWindow window;

	window.setWindowTitle("CuteHost");
	window.resize(800, 600);
	window.show();

	return a.exec();
}
