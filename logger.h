#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QTime>

class Logger
{
public:
	Logger(QString logName);
	~Logger();
	void _log(QString message);
	static void log(QString message);
	static void createInstance(QString logName);
	static Logger* getInstance();
	static void destroyInstance();
private:
	QFile* logFile;
	QString logName;
	static Logger* pInstance;
};

#endif // LOGGER_H
