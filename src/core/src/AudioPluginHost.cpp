#include "AudioPluginHost.hpp"

#include <JuceLibraryCode/JuceHeader.h>
#include <juce_audio_processors/format_types/juce_VST3PluginFormat.h>

namespace CuteHost {

AudioPluginHost::AudioPluginHost() : graph_(new juce::AudioProcessorGraph())
{
}

AudioPluginHost::~AudioPluginHost() = default;

void AudioPluginHost::scan()
{
	juce::KnownPluginList list;
	// juce::VST3PluginFormat format;
	// juce::PluginDirectoryScanner scanner(list, )
}

void AudioPluginHost::addPlugin(AudioPlugin::Ptr plugin)
{
	graph_->addNode(plugin->processor_.get());
}

} // namespace CuteHost
