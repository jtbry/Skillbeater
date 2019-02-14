#pragma once
#include <QDebug>
#include <QPixmap>
#include <QEvent>
#include <QString>
#include <QDebug>
#include <QScreen>
#include <QThread>
#include <QSize>
#include <QRect>
#include <QGuiApplication>

#include "Utilities.h"
#include "Module.h"

class Scanner
{
public:
	void Scan();
	Scanner(std::vector<Module*> *availableModulesPtr, QScreen* primaryDisplay);
	~Scanner();
private:
	bool shouldScan;
	QThread* scannerThread;
	QScreen *activeScreen;
	std::vector<Module*> *availableModules;
};

