#ifndef _CUTEHOST_JUCE_APPLICATION_HPP_
#define _CUTEHOST_JUCE_APPLICATION_HPP_

#include <QObject>
#include <QString>

#include <memory>
#include <thread>

namespace juce {
class JUCEApplication;
class Component;
class DocumentWindow;
} // namespace juce

namespace CuteHost {

/// juce::Application wrapper to use in Qt environment
class JuceApplication : public QObject
{
public:
	JuceApplication(const JuceApplication&) = delete;
	JuceApplication(JuceApplication&&) = delete;

	~JuceApplication();

	static juce::JUCEApplication& getApplication();

	static JuceApplication& instance();

public slots:
	void quit();

private:
	JuceApplication();

	std::unique_ptr<std::thread> thread_;
};

} // namespace CuteHost

#endif // _CUTEHOST_JUCE_APPLICATION_HPP_
