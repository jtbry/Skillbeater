#pragma once
#include <QColor>

class Pixel
{
public:
	bool isWhitePixel();
	bool isRedPixel();
	bool pixelInDist(int distance, Pixel pixel);
	Pixel(QColor pixelColor, int r, int c);
	Pixel();
	~Pixel();

	// Get
	int r();
	int g();
	int b();
	int row();
	int col();
	bool initialized();

	// Set (most-likely will not be used)
	void setR(int color);
	void setG(int color);
	void setB(int color);
	void setRow(int r);
	void setCol(int c);
private:
	bool pixelInitialized = false;
	int rVal; // red
	int gVal; // green
	int bVal; // blue
	int rowVal; // pixel row
	int colVal; // pixel col
};

