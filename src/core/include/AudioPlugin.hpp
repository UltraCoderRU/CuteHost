#ifndef _CUTEHOST_BASIC_PLUGIN_HPP_
#define _CUTEHOST_BASIC_PLUGIN_HPP_

#include <QObject>
#include <QString>
#include <QUuid>

#include <memory>

namespace juce {
class PluginDescription;
class AudioPluginInstance;
} // namespace juce

namespace CuteHost {

class PluginWindow;

enum class AudioPluginType
{
	VST3,
	VST2
};

enum class AudioPluginGroup
{
	Effect,
	Instrument,
	Other
};

/// juce::PluginDescription wrapper
class AudioPluginInfo
{
public:
	AudioPluginInfo(QUuid id, AudioPluginType type, const juce::PluginDescription& pluginDescription);
	AudioPluginInfo(const AudioPluginInfo&);
	AudioPluginInfo(AudioPluginInfo&&);
	AudioPluginInfo& operator=(AudioPluginInfo);

	QUuid id() const;
	AudioPluginType type() const;

	QString name() const;
	QString path() const;
	QString description() const;
	QString category() const;
	AudioPluginGroup group() const;
	QString manufacturerName() const;
	QString version() const;

	unsigned int inputCount() const;
	unsigned int outputCount() const;

	int internalId() const;

	juce::PluginDescription internalDescription() const;

	void swap(AudioPluginInfo&) noexcept;

private:
	QUuid id_;
	AudioPluginType type_;
	std::unique_ptr<juce::PluginDescription> internal_;
};

class PluginPort
{
public:
	enum Direction
	{
		Input,
		Output
	};

	enum Type
	{
		Mono,
		Stereo
	};

	PluginPort(Direction direction, QString name, Type type = Mono);

	Direction direction() const;
	Type type() const;
	const QString& name() const;

private:
	Direction direction_;
	Type type_;
	QString name_;
};

/// Plugin instance
class AudioPlugin final : public QObject
{
	Q_OBJECT
public:
	using Ptr = std::shared_ptr<AudioPlugin>;
	using Id = QUuid;
	using Type = AudioPluginType;
	using InstancePtr = std::shared_ptr<juce::AudioPluginInstance>;

	AudioPlugin(QUuid id, AudioPluginInfo info, InstancePtr instance);
	~AudioPlugin() override;

	/// Instance id
	Id id() const noexcept;

	/// Plugin information
	AudioPluginInfo info() const;

	/// List of plugin input ports
	const std::vector<PluginPort>& inputs() const;

	/// List of plugin output ports
	const std::vector<PluginPort>& outputs() const;

	void setBypass(bool);

	void showEditor();

private:
	void addPort(PluginPort port);

	Id id_;
	AudioPluginInfo info_;

	InstancePtr instance_;

	std::vector<PluginPort> inputs_;
	std::vector<PluginPort> outputs_;

	std::shared_ptr<PluginWindow> window_;

	friend class AudioPluginHost;
};

} // namespace CuteHost

Q_DECLARE_METATYPE(CuteHost::AudioPlugin::Ptr)

#endif // _BASIC_PLUGIN_HPP_
