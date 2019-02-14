#include "Skillbeater.h"

Skillbeater::Skillbeater(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	/* Install Event Filters */
	this->findChild<QWidget*>("title")->installEventFilter(this);
	
	/* Customize Window */
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	/* Load Image from URL */
	_httpReply = _netwrkAccessManager.get(QNetworkRequest((QUrl("http://i.imgur.com/g88eosP.gif"))));
	connect(_httpReply, &QNetworkReply::finished, this, &Skillbeater::httpReqFinished);
	connect(_httpReply, &QIODevice::readyRead, this, &Skillbeater::httpReqRead);

	/* Randomize title (avoid window-title scanning, ineffective against most prevention) */
	this->setWindowTitle(Util::generate_random_string(18).c_str());

	/* Set our modules that can be toggled */
	_screenScanner = new Scanner(&availableModules, QGuiApplication::primaryScreen());
	availableModules.push_back(new Solver("toggleSolver", "Screen"));
}

void Skillbeater::toggleFeature(int state) {
	QObject* checkbox = sender();
	for (int i = 0; i < availableModules.size(); i++) {
		if (checkbox->objectName() == availableModules.at(i)->getModuleName().c_str()) {
			availableModules.at(i)->toggle();
		}
	}
}

std::vector<Module*> Skillbeater::getAvailableModules()
{
	return availableModules;
}

void Skillbeater::httpReqFinished() {
	/* Set imageFrame's Pixmap to the downloaded data */
	if (_httpReply->error() != QNetworkReply::NoError) {
		this->close();
	}
	QLabel* imageFrame = this->findChild<QLabel*>("imageFrame");
	QPixmap downloadedImage;
	downloadedImage.loadFromData(_httpReplyBytes, "PNG");
	imageFrame->setScaledContents(true);
	imageFrame->setPixmap(downloadedImage);

}

void Skillbeater::httpReqRead() {
	_httpReplyBytes.append(_httpReply->readAll());
}

bool Skillbeater::eventFilter(QObject * obj, QEvent * event)
{
	/* Handle events in the main window (used for title bar text) */
	/* TODO: change to switch statement */
	if (event->type() == QEvent::MouseMove) {
		mouseMoveEvent(static_cast<QMouseEvent*>(event));
		return true;
	}
	else if (event->type() == QEvent::MouseButtonPress) {
		mousePressEvent(static_cast<QMouseEvent*>(event));
		return true;
	}
	else if (event->type() == QEvent::MouseButtonRelease) {
		mouseReleaseEvent(static_cast<QMouseEvent*>(event));
		return true;
	}
	else {
		return QObject::eventFilter(obj, event);
	}
}

void Skillbeater::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		_mouseBtnPressed = true;
		_mousePos = event->pos();
	}
}

void Skillbeater::mouseMoveEvent(QMouseEvent *event) {
	if (_mouseBtnPressed) {
		move(mapToParent(event->pos() - _mousePos));
	}
}
void Skillbeater::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		_mouseBtnPressed = false;
	}
}
