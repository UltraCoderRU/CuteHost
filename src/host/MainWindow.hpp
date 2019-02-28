#ifndef _CUTEHOST_MAIN_WINDOW_HPP_
#define _CUTEHOST_MAIN_WINDOW_HPP_

#include <QMainWindow>

namespace QtNodes {
class FlowScene;
}

namespace CuteHost {

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);

private slots:
	void loadWorkspace();
	void saveWorkspace();

private:
	void setupMenu();

	QtNodes::FlowScene* scene_;
};

} // namespace CuteHost

#endif // _CUTEHOST_MAIN_WINDOW_HPP_
