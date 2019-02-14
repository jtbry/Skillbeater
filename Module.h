#pragma once
#include <string>
#include <iostream>
#include <QThread>
#include <QDebug>
#include <QPixmap>
#include <QObject>

class Module : public QObject
{
public:
	void setModuleName(std::string name);
	void setModuleState(bool state);
	void setModuleThread(QThread* thread);
	void setModuleInitialized(bool b);
	void addModuleDependencies(std::string d);
	void setModuleBusy(bool b);

	bool isBusy();
	bool isModuleDependency(std::string name);
	bool isModuleInitialized();
	bool getModuleState();
	std::string getModuleName();
	QThread* getModuleThread();

	Module();
	Module(std::string name, std::string requires);
	~Module();

	virtual void toggle();
	virtual void start(QPixmap screen);
	virtual void start();
private:
	std::string moduleDependencies;
	bool moduleInitialized = false;
	bool moduleBusyStatus = false;
	std::string moduleName;
	bool moduleToggleState = false;
	QThread* moduleThread;
};

