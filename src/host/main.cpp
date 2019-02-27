#include "PluginDataModel.hpp"

#include <QApplication>

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/NodeData>

static std::shared_ptr<QtNodes::DataModelRegistry> registerDataModels()
{
	auto ret = std::make_shared<QtNodes::DataModelRegistry>();
	ret->registerModel<CuteHost::PluginDataModel>();
	return ret;
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QtNodes::FlowScene scene(registerDataModels());
	QtNodes::FlowView view(&scene);

	view.setWindowTitle("CuteHost");
	view.resize(800, 600);
	view.show();

	return app.exec();
}
