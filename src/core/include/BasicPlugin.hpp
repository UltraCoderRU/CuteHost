#ifndef _CUTEHOST_BASIC_PLUGIN_HPP_
#define _CUTEHOST_BASIC_PLUGIN_HPP_

#include <QObject>
#include <QString>

#include <memory>

namespace CuteHost {

class PluginPort
{
public:
	enum Direction
	{
		Input,
		Output
	};

	enum Type
	{
		Mono,
		Stereo
	};

	PluginPort(Direction direction, Type type, QString name);

	Direction direction() const;
	Type type() const;
	const QString& name() const;

private:
	Direction direction_;
	Type type_;
	QString name_;
};

class Plugin : public QObject
{
	Q_OBJECT
public:
	using Ptr = std::shared_ptr<Plugin>;

	enum Type
	{
		VST3,
		LV2
	};

	Type type() const noexcept;
	const QString& name() const noexcept;


signals:
	void test();

protected:
	void setName(QString name);
	void addPort(PluginPort port);

private:
	std::vector<PluginPort> inputs_;
	std::vector<PluginPort> outputs_;
};

} // namespace CuteHost

#endif // _BASIC_PLUGIN_HPP_
