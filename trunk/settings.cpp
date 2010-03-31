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

void Settings::setProp(QString propName, QVariant value){
	s->setValue(propName,value);
}

void Settings::toggle(QString propName){
	setProp(propName,getProp(propName,"0").toInt()==0?1:0);
}

void Settings::increment(QString propName, int value){
	setProp(propName,getProp(propName,"0").toInt()+value);
}
