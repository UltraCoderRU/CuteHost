#ifndef _CUTEHOST_AUDIO_PLUGIN_LOADER_HPP_
#define _CUTEHOST_AUDIO_PLUGIN_LOADER_HPP_

#include "AudioPlugin.hpp"

namespace juce {
class AudioPluginFormatManager;
}

namespace CuteHost {

class AudioPluginLoader
{
public:
	static AudioPlugin::Ptr load(AudioPluginInfo info, unsigned int sampleRate);

	static AudioPluginLoader& instance();

private:
	AudioPluginLoader();

	std::unique_ptr<juce::AudioPluginFormatManager> manager_;
};

} // namespace CuteHost

#endif // _CUTEHOST_AUDIO_PLUGIN_LOADER_HPP_
