#include "PluginDataModel.hpp"

namespace CuteHost {

QtNodes::NodeDataType PluginNodeData::type() const
{
	return QtNodes::NodeDataType{"PluginNodeData", "Plugin Node Data"};
}

Plugin::Ptr PluginNodeData::plugin()
{
	return plugin_;
}

//////////////////////////////////////

QString PluginDataModel::caption() const
{
	return "Plugin";
}

QString PluginDataModel::name() const
{
	return "PluginDataModel";
}

QJsonObject PluginDataModel::save() const
{
	QJsonObject modelJson;
	modelJson["name"] = name();
	return modelJson;
}

unsigned int PluginDataModel::nPorts(QtNodes::PortType type) const
{
	return 2;
}

QtNodes::NodeDataType PluginDataModel::dataType(QtNodes::PortType, QtNodes::PortIndex) const
{
	return PluginNodeData().type();
}

std::shared_ptr<QtNodes::NodeData> PluginDataModel::outData(QtNodes::PortIndex)
{
	return std::make_shared<PluginNodeData>();
}

void PluginDataModel::setInData(std::shared_ptr<QtNodes::NodeData>, int)
{
	// TODO ???
}

QWidget* PluginDataModel::embeddedWidget()
{
	return nullptr;
}

} // namespace CuteHost
