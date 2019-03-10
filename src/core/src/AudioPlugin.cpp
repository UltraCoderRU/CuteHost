#include "AudioPlugin.hpp"

#include "JuceApplication.hpp"
#include "PluginWindow.hpp"
#include "Utils.hpp"

#include <JuceHeader.h>

#include <memory>
#include <utility>

namespace CuteHost {

AudioPluginInfo::AudioPluginInfo(QUuid id,
                                 AudioPluginType type,
                                 const juce::PluginDescription& pluginDescription)
    : id_(id), type_(type), internal_(new juce::PluginDescription(pluginDescription))
{
}

AudioPluginInfo::AudioPluginInfo(const AudioPluginInfo& other)
    : id_(other.id_), type_(other.type_), internal_(new juce::PluginDescription(*other.internal_))
{
}

AudioPluginInfo::AudioPluginInfo(AudioPluginInfo&&) = default;

QUuid AudioPluginInfo::id() const
{
	return id_;
}

AudioPluginType AudioPluginInfo::type() const
{
	return type_;
}

QString AudioPluginInfo::name() const
{
	return qstr(internal_->name);
}

QString AudioPluginInfo::path() const
{
	return qstr(internal_->fileOrIdentifier);
}

QString AudioPluginInfo::description() const
{
	return qstr(internal_->descriptiveName);
}

QString AudioPluginInfo::category() const
{
	return qstr(internal_->category);
}

AudioPluginGroup AudioPluginInfo::group() const
{
	return internal_->isInstrument ? AudioPluginGroup::Instrument : AudioPluginGroup::Effect;
}

QString AudioPluginInfo::manufacturerName() const
{
	return qstr(internal_->manufacturerName);
}

QString AudioPluginInfo::version() const
{
	return qstr(internal_->version);
}

unsigned int AudioPluginInfo::inputCount() const
{
	return static_cast<unsigned int>(internal_->numInputChannels);
}

unsigned int AudioPluginInfo::outputCount() const
{
	return static_cast<unsigned int>(internal_->numOutputChannels);
}

int AudioPluginInfo::internalId() const
{
	return internal_->uid;
}

juce::PluginDescription AudioPluginInfo::internalDescription() const
{
	return *internal_;
}

void AudioPluginInfo::swap(AudioPluginInfo& other) noexcept
{
	using std::swap;
	swap(id_, other.id_);
	swap(type_, other.type_);
	swap(internal_, other.internal_);
}

AudioPluginInfo& AudioPluginInfo::operator=(AudioPluginInfo other)
{
	swap(other);
	return *this;
}

/////////////////////////////////////////

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

AudioPlugin::AudioPlugin(QUuid id, AudioPluginInfo info, InstancePtr instance)
    : id_(id), info_(std::move(info)), instance_(std::move(instance))
{
	// TODO Create ports
}

AudioPlugin::~AudioPlugin() = default;

AudioPlugin::Id AudioPlugin::id() const noexcept
{
	return id_;
}

AudioPluginInfo AudioPlugin::info() const
{
	return info_;
}

void AudioPlugin::setBypass(bool value)
{
	instance_->getBypassParameter()->setValue(value);
}

const std::vector<PluginPort>& AudioPlugin::inputs() const
{
	return inputs_;
}

const std::vector<PluginPort>& AudioPlugin::outputs() const
{
	return outputs_;
}

void AudioPlugin::showEditor()
{
	if (window_)
	{
		window_->toFront(true);
		return;
	}

	if (instance_->hasEditor())
	{
		qInfo().noquote() << QString("Creating GUI editor for plugin '%1'...").arg(info_.name());
		juce::AudioProcessorEditor* editor = instance_->createEditorIfNeeded();
		if (editor)
		{
			window_ = std::make_shared<PluginWindow>(info_.name(), editor,
			                                         JuceApplication::getApplication());
			connect(window_.get(), &PluginWindow::closed, this, [&] { window_.reset(); });
			return;
		}
		else
		{
			qCritical() << "Can not create editor.";
		}
	}
	else
	{
		qWarning() << "Plugin has no editor.";
	}
}

} // namespace CuteHost
