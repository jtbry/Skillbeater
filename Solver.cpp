#include "Solver.h"

void Solver::start(QPixmap displayImage)
{
	displayImage = displayImage.copy(0, 0, (((displayImage.width() / 10) * 10) + 10), (((displayImage.height() / 10) * 10) + 10));

	//_debug_imageLabel->setPixmap(displayImage);
	QRect solveTarget;
	if (isImageSkillcheck(displayImage.toImage(), solveTarget) && !isBusy()) {
		setModuleBusy(true);
		setModuleThread(QThread::create([this, solveTarget] {
			beginSolving(solveTarget);
		}));
		getModuleThread()->start();
		connect(getModuleThread(), &QThread::finished, this, &Solver::endSolving);
	}
}

Solver::Solver(std::string name, std::string requires)
{
	setModuleName(name);
	addModuleDependencies(requires);
	setModuleInitialized(true);

	//_debug_imageDisplay = new QDialog();
	//_debug_imageDisplay->setWindowTitle("SKILLBEATER DEBUG PREVIEW");
	//_debug_imageDisplay->resize(300, 300);
	//_debug_imageLabel = new QLabel(_debug_imageDisplay);
	//_debug_imageLabel->setText("image label");
	//_debug_imageLabel->setStyleSheet("QLabel { background-color: red; }");
	//_debug_imageLabel->resize(_debug_imageDisplay->size());
	//_debug_imageDisplay->show();
}

Solver::~Solver()
{
	delete this;
}

bool Solver::isImageSkillcheck(QImage img, QRect &solveArea)
{
	// Determine which block has the most white pixels
	int best_block_density = 0;
	Pixel best_block;

	for (int block_y = 0; block_y <= img.height() - 10; block_y += 10) {
		for (int block_x = 0; block_x <= img.width() - 10; block_x += 10) {
			int blockDensityScore = 0;
			for (int c = block_y; c < block_y + 10; c++) {
				for (int r = block_x; r < block_x + 10; r++) {
					if (Pixel(img.pixelColor(r, c), r, c).isWhitePixel()) {
						blockDensityScore += 1;
					}
				}
			}

			if (blockDensityScore > best_block_density) {
				best_block = Pixel(img.pixelColor(block_x, block_y), block_x, block_y);
				best_block_density = blockDensityScore;
			}

		}
	}

	if (best_block_density >= 10) {
		qDebug() << "DENSITY CHECK: " << best_block.row() << "x" << best_block.col() << " with " << best_block_density;
		solveArea = QRect(best_block.row() - 1, best_block.col() - 1, 10, 10);
		return true;
	}

	// If not returned by now, it's false.
	return false;
}

void Solver::beginSolving(QRect solveArea)
{
	QApplication::beep();
	auto solve_start_time = std::chrono::steady_clock::now();
	bool isSolved = false;
	QScreen* screen = QGuiApplication::primaryScreen();
	while (!isSolved) {
		if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - solve_start_time).count() >= 2) {
			break;
		}

		QThread::msleep(10);
		QSize offset((screen->size().width() * .44) + solveArea.x()-2, (screen->size().height() * .40) + solveArea.y()-2);
		QSize size(10, 10);
		QImage img = screen->grabWindow(0, offset.width(), offset.height(), size.width(), size.height()).toImage();
	
		int red_pixel_density = 0;
		for (int c = 0; c < img.height(); c++) {
			for (int r = 0; r < img.width(); r++) {
				if (Pixel(img.pixelColor(r, c), r, c).isRedPixel()) {
					red_pixel_density += 1;
				}
			}
		}

		if (red_pixel_density >= 1) {
			isSolved = true;
			pressSpaceKey();
			QThread::msleep(1300);
		}
	}
}

void Solver::pressSpaceKey()
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	input.ki.wVk = VK_SPACE;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void Solver::endSolving() {
	if (getModuleThread()->isRunning()) {
		getModuleThread()->terminate();
	}
	setModuleThread(new QThread());
	setModuleBusy(false);
	disconnect(this, &Solver::endSolving, 0, 0);
}
