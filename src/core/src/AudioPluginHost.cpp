#include "AudioPluginHost.hpp"

#include "AudioPluginLibrary.hpp"
#include "AudioPluginLoader.hpp"
#include "JuceApplication.hpp"
#include "PluginWindow.hpp"

#include <JuceHeader.h>

#include <QDebug>

#include <thread>

namespace CuteHost {

AudioPluginHost::AudioPluginHost()
    : graph_(new juce::AudioProcessorGraph()),
      pluginManager_(new juce::AudioPluginFormatManager()),
      sampleRate_(44100)
{
}

AudioPluginHost::~AudioPluginHost() = default;

AudioPlugin::Ptr AudioPluginHost::loadPlugin(const QUuid& id)
{
	AudioPlugin::Ptr plugin;

	AudioPluginLibrary& library = AudioPluginLibrary::instance();
	auto info = library.findPluginByName("FabFilter Pro-Q 3");
	if (info)
		qInfo() << "Plugin found!";

	plugin = AudioPluginLoader::load(std::move(*info), sampleRate_);
	plugins_[plugin->id()] = plugin;

	graph_->addNode(plugin->instance_.get());

	showEditor(plugin->id());

	return plugin;
}

void AudioPluginHost::unloadPlugin(const QUuid& id)
{
	qDebug() << "Removing plugin";

	auto iter = std::find_if(plugins_.begin(), plugins_.end(),
	                         [=](std::pair<AudioPlugin::Id, AudioPlugin::Ptr> elem) {
		                         return elem.second->info_.name() == "FabFilter Pro-Q 3";
	                         });

	if (iter != plugins_.end())
		plugins_.erase(iter);
}

void AudioPluginHost::showEditor(const QUuid& id)
{
	AudioPlugin::Ptr plugin = getPluginById(id);
	if (plugin)
		plugin->showEditor();
}

AudioPlugin::Ptr AudioPluginHost::getPluginById(const QUuid& id)
{
	auto iter = plugins_.find(id);
	if (iter != plugins_.end())
		return iter->second;
	return nullptr;
}

} // namespace CuteHost
