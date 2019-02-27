#ifndef _CUTEHOST_PLUGIN_DATA_MODEL_HPP_
#define _CUTEHOST_PLUGIN_DATA_MODEL_HPP_

#include "BasicPlugin.hpp"

#include <QObject>

#include <memory>
#include <nodes/NodeData>
#include <nodes/NodeDataModel>

namespace CuteHost {

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class PluginNodeData : public QtNodes::NodeData
{
public:
	QtNodes::NodeDataType type() const override;
	Plugin::Ptr plugin();

private:
	Plugin::Ptr plugin_;
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class PluginDataModel : public QtNodes::NodeDataModel
{
	Q_OBJECT

public:
	QString caption() const override;
	QString name() const override;
	QJsonObject save() const override;
	unsigned int nPorts(QtNodes::PortType type) const override;

	QtNodes::NodeDataType dataType(QtNodes::PortType, QtNodes::PortIndex) const override;
	std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex) override;

	void setInData(std::shared_ptr<QtNodes::NodeData>, int) override;

	QWidget* embeddedWidget() override;
};

} // namespace CuteHost

#endif // _CUTEHOST_PLUGIN_DATA_MODEL_HPP_
