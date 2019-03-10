#include "JuceApplication.hpp"

#include <JuceHeader.h>

#include <QDebug>

#include <JuceApplication.hpp>


using namespace juce;

namespace CuteHost {

namespace {

class Application : public JUCEApplication
{
public:
	Application() = default;

	const String getApplicationName() override { return "CuteHost"; }
	const String getApplicationVersion() override { return "1.0.0"; }

	void initialise(const String&) override {}
	void shutdown() override {}
};

JUCE_CREATE_APPLICATION_DEFINE(Application)

void juceWorker()
{
	qInfo() << "Starting JUCEApplication...";
	juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
	juce::JUCEApplicationBase::main();
	qInfo() << "JUCEApplication closed";
}

} // namespace

juce::JUCEApplication& JuceApplication::getApplication()
{
	return *juce::JUCEApplication::getInstance();
}

JuceApplication& JuceApplication::instance()
{
	static JuceApplication instance;
	return instance;
}

JuceApplication::~JuceApplication()
{
	quit();
}

void JuceApplication::quit()
{
	if (thread_)
	{
		juce::JUCEApplicationBase::quit();
		thread_->join();
		thread_.reset();
	}
}

JuceApplication::JuceApplication()
{
	thread_ = std::make_unique<std::thread>(juceWorker);
}

} // namespace CuteHost
