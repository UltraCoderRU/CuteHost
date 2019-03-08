#include "AudioPlugin.hpp"

#include <JuceLibraryCode/JuceHeader.h>

#include <utility>

namespace CuteHost {

PluginPort::PluginPort(Direction direction, QString name, Type type)
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

void AudioPlugin::addPort(PluginPort port)
{
	if (port.direction() == PluginPort::Input)
		inputs_.push_back(std::move(port));
	else
		outputs_.push_back(std::move(port));
}

/////////////////////////////////////////

AudioPlugin::AudioPlugin(std::shared_ptr<juce::AudioProcessor> processor) : processor_(processor)
{
	name_ = QString::fromStdString(processor_->getName().toStdString());
}

AudioPlugin::~AudioPlugin() = default;

AudioPlugin::Type AudioPlugin::type() const noexcept
{
	return type_;
}

const QString& AudioPlugin::name() const noexcept
{
	return name_;
}

void AudioPlugin::setBypass(bool value)
{
	processor_->getBypassParameter()->setValue(value);
}

} // namespace CuteHost
