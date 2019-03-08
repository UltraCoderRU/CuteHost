#ifndef _CUTEHOST_AUDIO_PLUGIN_HOST_HPP_
#define _CUTEHOST_AUDIO_PLUGIN_HOST_HPP_

#include "AudioPlugin.hpp"

#include <QObject>

namespace juce {
class AudioProcessorGraph;
}

namespace CuteHost {

class AudioPluginHost : public QObject
{
	Q_OBJECT
public:
	AudioPluginHost();
	~AudioPluginHost() override;

	void scan();
	void addPlugin(AudioPlugin::Ptr plugin);

private:
	std::shared_ptr<juce::AudioProcessorGraph> graph_;
};

} // namespace CuteHost

#endif // _CUTEHOST_AUDIO_PLUGIN_HOST_HPP_
