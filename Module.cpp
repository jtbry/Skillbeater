#include "Module.h"




void Module::setModuleName(std::string name)
{
	moduleName = name;
}

void Module::setModuleState(bool state)
{
	moduleToggleState = state;
}

void Module::setModuleThread(QThread* thread)
{
	moduleThread = thread;
}

void Module::setModuleInitialized(bool initialized)
{
	moduleInitialized = initialized;
}

void Module::addModuleDependencies(std::string d)
{
	moduleDependencies += (std::string(";") += d);
}

void Module::setModuleBusy(bool b)
{
	moduleBusyStatus = b;
}

bool Module::isBusy()
{
	return moduleBusyStatus;
}

bool Module::isModuleDependency(std::string name)
{
	if (moduleDependencies.find(std::string(";") += name) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}

bool Module::isModuleInitialized()
{
	return moduleInitialized;
}

bool Module::getModuleState()
{
	return moduleToggleState;
}

std::string Module::getModuleName()
{
	return moduleName;
}

QThread * Module::getModuleThread()
{
	return moduleThread;
}

void Module::toggle()
{
	moduleToggleState = !moduleToggleState;
}

void Module::start(QPixmap screen)
{
	return;
}

void Module::start()
{
	return;
}

Module::Module()
{
	moduleInitialized = false;
}

Module::Module(std::string name, std::string dependencies)
{
	moduleName = name;
	moduleDependencies += (std::string(";") += dependencies);
	moduleInitialized = true;
}


Module::~Module()
{
	moduleInitialized = false;
}
