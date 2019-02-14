#pragma once

#include <QtWidgets/QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QNetworkReply>
#include <QDebug>
#include <QPixmap>
#include <QMovie>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QByteArray>
#include <QString>

#include "Module.h"
#include "Scanner.h"
#include "Solver.h"
#include "Utilities.h"
#include "ui_Skillbeater.h"

class Skillbeater : public QMainWindow
{
	Q_OBJECT

public:
	Skillbeater(QWidget *parent = Q_NULLPTR);
	std::vector<Module*> getAvailableModules();
public slots:
	void toggleFeature(int state);
	void httpReqFinished();
	void httpReqRead();
private:
	Scanner* _screenScanner = nullptr;
	Ui::SkillbeaterClass ui;

	/* Related to Image Download */
	QNetworkAccessManager _netwrkAccessManager;
	QNetworkReply* _httpReply;
	QByteArray _httpReplyBytes;

	/* Related to Custom Drag */
	bool eventFilter(QObject *obj, QEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent* event);
	bool _mouseBtnPressed = false;
	QPoint _mousePos = QPoint();

	/* Related to Feature Toggling */
	bool _toggleSolver = false;
	std::vector<Module*> availableModules;


};

