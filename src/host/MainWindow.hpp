#ifndef _CUTEHOST_MAIN_WINDOW_HPP_
#define _CUTEHOST_MAIN_WINDOW_HPP_

#include <QMainWindow>

#include <memory>

namespace QtNodes {
class FlowScene;
}

namespace CuteHost {

class AudioPluginHost;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

private slots:
	void loadWorkspace();
	void saveWorkspace();

private:
	void setupMenu();

	QtNodes::FlowScene* scene_;
	std::shared_ptr<AudioPluginHost> pluginHost_;
};

} // namespace CuteHost

#endif // _CUTEHOST_MAIN_WINDOW_HPP_
