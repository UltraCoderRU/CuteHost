#include "AudioPluginLibrary.hpp"

#include "Utils.hpp"

#include <JuceLibraryCode/JuceHeader.h>

#include <QDebug>

namespace CuteHost {

void AudioPluginLibrary::scan(const std::function<void(float)>& progressCallback,
                              const std::function<bool()>& wasCanceled)
{
	juce::KnownPluginList list;
	juce::VST3PluginFormat format;
	juce::PluginDirectoryScanner scanner(list, format, format.getDefaultLocationsToSearch(), true,
	                                     juce::File(), false);
	juce::String currentPlugin;

	while (!wasCanceled() && scanner.scanNextFile(false, currentPlugin))
	{
		auto pluginInfo = list.getType(0);
		plugins_.emplace_back(QUuid::createUuid(), AudioPluginType::VST3, *pluginInfo);
		qInfo().noquote()
		    << QString("Found plugin: '%1' [%2]").arg(qstr(pluginInfo->name)).arg(qstr(currentPlugin));
		progressCallback(scanner.getProgress());
	}
	qInfo() << "Scanning completed";

	progressCallback(1.0);
}

std::optional<AudioPluginInfo> AudioPluginLibrary::findPluginById(const QUuid& id)
{
	auto result = std::find_if(plugins_.cbegin(), plugins_.cend(),
	                           [&id](const AudioPluginInfo& info) { return info.id() == id; });

	if (result != plugins_.end())
	{
		return *result;
	}
	return std::nullopt;
}

std::optional<AudioPluginInfo> AudioPluginLibrary::findPluginByName(const QString& name)
{
	auto result = std::find_if(plugins_.cbegin(), plugins_.cend(),
	                           [&name](const AudioPluginInfo& info) { return info.name() == name; });

	if (result != plugins_.end())
	{
		return *result;
	}
	return std::nullopt;
}

AudioPluginLibrary& AudioPluginLibrary::instance()
{
	static AudioPluginLibrary instance;
	return instance;
}

AudioPluginLibrary::AudioPluginLibrary()
{
}

} // namespace CuteHost
