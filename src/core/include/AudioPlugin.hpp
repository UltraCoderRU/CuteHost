#ifndef _CUTEHOST_BASIC_PLUGIN_HPP_
#define _CUTEHOST_BASIC_PLUGIN_HPP_

#include <QObject>
#include <QString>

#include <memory>

namespace juce {
class AudioProcessor;
}

namespace CuteHost {

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

class AudioPlugin final : public QObject
{
	Q_OBJECT
public:
	using Ptr = std::shared_ptr<AudioPlugin>;
	using Id = QUuid;

	enum Type
	{
		VST3,
		VST2
	};

	explicit AudioPlugin(std::shared_ptr<juce::AudioProcessor> processor);
	~AudioPlugin() override;

	Type type() const noexcept;
	const QString& name() const noexcept;

	void setBypass(bool);

private:
	void addPort(PluginPort port);

	Type type_;
	QString name_;

	std::shared_ptr<juce::AudioProcessor> processor_;

	std::vector<PluginPort> inputs_;
	std::vector<PluginPort> outputs_;

	friend class AudioPluginHost;
};

} // namespace CuteHost

#endif // _BASIC_PLUGIN_HPP_
