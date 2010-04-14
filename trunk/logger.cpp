#include "logger.h"

Logger* Logger::pInstance=NULL;

Logger::Logger(QString logName):logName(logName)
{
	logFile = new QFile(logName);
}

Logger::~Logger(){
	delete logFile;
}

void Logger::_log(QString message){
	qDebug() << "log: " << message;
	logFile->open(QIODevice::Append);
	logFile->write(QString(QTime::currentTime().toString("hh:mm:ss.zzz: ")+message+"\n").toAscii());
	logFile->close();
}

void Logger::log(QString message){
	getInstance()->_log(message);
}

void Logger::createInstance(QString logName){
	if(pInstance!=NULL)
		qDebug() << "Logger: create instance called twice";
	pInstance = new Logger(logName);
}

Logger* Logger::getInstance(){
	if(!pInstance){
		pInstance = new Logger("log.txt");
		qDebug() << "Logger: get instance without create";
	}
	return pInstance;
}

void Logger::destroyInstance(){
	if(pInstance==NULL)
		qDebug() << "Logger: destroying null class";
	else{
		delete pInstance;
		pInstance=NULL;
	}
}

