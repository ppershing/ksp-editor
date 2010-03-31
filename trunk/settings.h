#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
    Settings();
	void load();
	QVariant getProp(QString propName,QVariant def=NULL);
	void setProp(QString propName,QVariant value);
	void toggle(QString propName);
	void increment(QString propName,int value=1);
private:
	QSettings* s;
	QMap<QString,QVariant> prop;
};

#endif // SETTINGS_H
