#include "Utils.hpp"

#include <JuceHeader.h>

namespace CuteHost {

QString qstr(const std::string& str)
{
	return QString::fromStdString(str);
}

QString qstr(const juce::String& str)
{
	return QString::fromStdString(str.toStdString());
}

QDebug operator<<(QDebug& debug, const std::string& str)
{
	debug << qstr(str);
	return debug;
}

QDebug operator<<(QDebug& debug, const juce::String& str)
{
	debug << qstr(str);
	return debug;
}

} // namespace CuteHost
