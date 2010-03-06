#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
    Settings();
	void load();
	QVariant getProp(QString propName,QVariant def=NULL);

private:
	QSettings* s;
	QMap<QString,QVariant> prop;
};

#endif // SETTINGS_H
