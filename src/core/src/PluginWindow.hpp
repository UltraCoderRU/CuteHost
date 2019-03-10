#ifndef _CUTEHOST_PLUGIN_WINDOW_HPP_
#define _CUTEHOST_PLUGIN_WINDOW_HPP_

#include <JuceHeader.h>

#include <QObject>

namespace CuteHost {

class PluginWindow : public QObject, public juce::DocumentWindow
{
	Q_OBJECT
public:
	PluginWindow(const QString& name, Component* component, juce::JUCEApplication& a)
	    : DocumentWindow(name.toStdString(),
	                     juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
	                         ResizableWindow::backgroundColourId),
	                     juce::DocumentWindow::minimiseButton | DocumentWindow::closeButton),
	      app_(a)
	{
		setUsingNativeTitleBar(true);
		setResizable(false, false);
		setContentOwned(component, true);
		centreWithSize(getWidth(), getHeight());
		setVisible(true);
	}

	~PluginWindow() override { clearContentComponent(); }

	void closeButtonPressed() override { emit closed(); }

	//	int getDesktopWindowStyleFlags() const override
	//	{
	//		int flags = DocumentWindow::getDesktopWindowStyleFlags();
	//		flags &= ~(ComponentPeer::windowAppearsOnTaskbar);
	//		return flags;
	//	}

signals:
	void closed();

private:
	juce::JUCEApplication& app_;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginWindow)
};

} // namespace CuteHost

#endif // _CUTEHOST_PLUGIN_WINDOW_HPP_
