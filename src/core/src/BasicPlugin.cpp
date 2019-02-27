#include "BasicPlugin.hpp"

#include <utility>

namespace CuteHost {

PluginPort::PluginPort(Direction direction, Type type, QString name)
    : direction_(direction), type_(type), name_(std::move(name))
{
}

PluginPort::Direction PluginPort::direction() const
{
	return direction_;
}

PluginPort::Type PluginPort::type() const
{
	return type_;
}

const QString& PluginPort::name() const
{
	return name_;
}

void Plugin::addPort(PluginPort port)
{
	if (port.direction() == PluginPort::Input)
		inputs_.push_back(std::move(port));
	else
		outputs_.push_back(std::move(port));
}

} // namespace CuteHost
