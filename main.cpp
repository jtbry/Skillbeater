#include "Skillbeater.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Skillbeater w;
	w.show();
	return a.exec();
}
