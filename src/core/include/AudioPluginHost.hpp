#ifndef _CUTEHOST_AUDIO_PLUGIN_HOST_HPP_
#define _CUTEHOST_AUDIO_PLUGIN_HOST_HPP_

#include "AudioPlugin.hpp"

#include <QObject>

#include <map>

namespace juce {
class AudioProcessorGraph;
class AudioPluginFormatManager;
} // namespace juce

namespace CuteHost {

class AudioPluginHost final : public QObject
{
	Q_OBJECT
public:
	AudioPluginHost();
	~AudioPluginHost() override;

	AudioPlugin::Ptr loadPlugin(const QUuid& id);
	void unloadPlugin(const QUuid& id);

	void showEditor(const QUuid& id);

	AudioPlugin::Ptr getPluginById(const QUuid& id);

signals:
	void newPlugin(AudioPlugin::Ptr);

private:
	std::map<AudioPlugin::Id, AudioPlugin::Ptr> plugins_;
	std::unique_ptr<juce::AudioProcessorGraph> graph_;
	std::unique_ptr<juce::AudioPluginFormatManager> pluginManager_;

	unsigned int sampleRate_;
};

} // namespace CuteHost

#endif // _CUTEHOST_AUDIO_PLUGIN_HOST_HPP_
