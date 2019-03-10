#ifndef _CUTEHOST_AUDIO_PLUGIN_LIBRARY_H_
#define _CUTEHOST_AUDIO_PLUGIN_LIBRARY_H_

#include "AudioPlugin.hpp"

#include <QObject>

#include <functional>
#include <optional>

namespace juce {
class KnownPluginList;
}

namespace CuteHost {

class AudioPluginLibrary : public QObject
{
	Q_OBJECT
public:
	void scan(const std::function<void(float)>& progressCallback,
	          const std::function<bool(void)>& wasCanceled);

	std::optional<AudioPluginInfo> findPluginById(const QUuid&);
	std::optional<AudioPluginInfo> findPluginByName(const QString&);

	static AudioPluginLibrary& instance();

private:
	AudioPluginLibrary();

	std::vector<AudioPluginInfo> plugins_;
};

} // namespace CuteHost

#endif // _CUTEHOST_AUDIO_PLUGIN_LIBRARY_H_
