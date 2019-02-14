#include "Scanner.h"

void Scanner::Scan() {
	while (shouldScan) {
		QThread::msleep(100);
		std::vector<Module*> modulesRequireScreen;
		for (int i = 0; i < availableModules->size(); i++) {
			if (availableModules->at(i)->isModuleInitialized() && availableModules->at(i)->getModuleState() && availableModules->at(i)->isModuleDependency("Screen") && !availableModules->at(i)->isBusy()) {
				modulesRequireScreen.push_back(availableModules->at(i));
			}
		}

		if (modulesRequireScreen.size() > 0) {
			QSize grabScreenOffset(activeScreen->size().width() * .44, activeScreen->size().height() * .40);
			QSize grabScreenSize(activeScreen->size().width() * .13, activeScreen->size().height() * .18);

			QPixmap grabbedScreen = activeScreen->grabWindow(0, grabScreenOffset.width(), grabScreenOffset.height(), grabScreenSize.width(), grabScreenSize.height());
			for (int i = 0; i < modulesRequireScreen.size(); i++) {
				modulesRequireScreen.at(i)->start(grabbedScreen);
			}
		}
	}
}

Scanner::Scanner(std::vector<Module*>* availableModulesPtr, QScreen* primaryDisplay)
{
	activeScreen = primaryDisplay;
	availableModules = availableModulesPtr;
	shouldScan = true;
	scannerThread = QThread::create([this] { Scan(); });
	scannerThread->start();
}

Scanner::~Scanner()
{
	shouldScan = false;
	if (scannerThread->isRunning()) {
		scannerThread->terminate();
	}
	delete scannerThread;
	delete availableModules;
	delete activeScreen;
}
