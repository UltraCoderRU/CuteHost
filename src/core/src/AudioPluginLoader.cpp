#include "AudioPluginLoader.hpp"

#include "Utils.hpp"

#include <JuceLibraryCode/JuceHeader.h>

#include <QDebug>

namespace CuteHost {

AudioPlugin::Ptr AudioPluginLoader::load(AudioPluginInfo info, unsigned int sampleRate)
{
	AudioPlugin::Ptr plugin;

	qDebug().noquote() << QString("Loading plugin '%1'...").arg(info.path());
	juce::String error;
	std::shared_ptr<juce::AudioPluginInstance> pluginInstance(
	    instance().manager_->createPluginInstance(info.internalDescription(), sampleRate, 512, error));
	if (pluginInstance)
	{
		plugin = std::make_shared<AudioPlugin>(QUuid::createUuid(), std::move(info), pluginInstance);
		qInfo() << "Plugin loaded.";
		return plugin;
	}
	else
	{
		qCritical() << "Can not load plugin:" << error;
		return nullptr;
	}
}

AudioPluginLoader& AudioPluginLoader::instance()
{
	static AudioPluginLoader instance;
	return instance;
}

AudioPluginLoader::AudioPluginLoader() : manager_(new juce::AudioPluginFormatManager())
{
	manager_->addDefaultFormats();
}

} // namespace CuteHost
