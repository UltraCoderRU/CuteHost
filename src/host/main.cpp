#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	CuteHost::MainWindow window;

	window.setWindowTitle("CuteHost");
	window.resize(800, 600);
	window.show();

	return a.exec();
}
