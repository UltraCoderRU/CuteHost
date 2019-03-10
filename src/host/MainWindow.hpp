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
	explicit MainWindow();
	~MainWindow() override;

private slots:
	void loadWorkspace();
	void saveWorkspace();

	void insertPlugin();
	void removePlugin();
	void scanForPlugins();

	void showAboutDialog();

private:
	void setupMenu();

	QtNodes::FlowScene* scene_;
	std::unique_ptr<AudioPluginHost> pluginHost_;
};

} // namespace CuteHost

#endif // _CUTEHOST_MAIN_WINDOW_HPP_
