#include "settings.h"

Settings::Settings()
{
}

void Settings::load(){
	s = new QSettings("settings.ini",QSettings::IniFormat);
}

QVariant Settings::getProp(QString propName, QVariant def){
	return s->value(propName,def);
}
