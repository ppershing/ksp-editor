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

bool Settings::getBool(QString propName){
	return s->value(propName,false).toBool();
}

int Settings::getInt(QString propName){
	return s->value(propName,0).toInt();
}

QString Settings::getString(QString propName){
	return s->value(propName,"").toString();
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

void Settings::decrement(QString propName, int value){
	increment(propName,-value);
}
