#ifndef _CUTEHOST_UTILS_HPP_
#define _CUTEHOST_UTILS_HPP_

#include <QDebug>

#include <string>

namespace juce {
class String;
}

namespace CuteHost {

QString qstr(const std::string&);
QString qstr(const juce::String&);

QDebug operator<<(QDebug& debug, const std::string&);
QDebug operator<<(QDebug& debug, const juce::String&);

} // namespace CuteHost

#endif // _CUTEHOST_UTILS_HPP_
