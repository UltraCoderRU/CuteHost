#include "JuceApplication.hpp"
#include "MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	a.setApplicationVersion(CUTEHOST_APPLICATION_VERSION);

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

	auto& juceApp = CuteHost::JuceApplication::instance();
	QObject::connect(&a, &QApplication::aboutToQuit, &juceApp, &CuteHost::JuceApplication::quit);

	CuteHost::MainWindow window;

	window.setWindowTitle("CuteHost");
	window.resize(800, 600);
	window.show();

	return a.exec();
}
