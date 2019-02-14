#pragma once
#include "Module.h"
#include "Pixel.h"

#include <chrono>
#include <QDebug>
#include <QPixmap>
#include <QObject>
#include <QImage>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QPainter>
#include <QApplication>
#include <Windows.h>
/* DEBUGGING WINDOW INCLUDES */
#include <QDialog>
#include <QLabel>

class Solver : public Module
{
	Q_OBJECT
public:
	void start(QPixmap displayImage);
	Solver(std::string name, std::string requires);
	~Solver();
public slots:
	void endSolving();
private:
	bool isImageSkillcheck(QImage img, QRect &solveArea);
	void beginSolving(QRect solveArea);
	void pressSpaceKey();

	//QDialog *_debug_imageDisplay;
	//QLabel* _debug_imageLabel;
};

