#include "Pixel.h"

Pixel::~Pixel()
{
	rVal = 0;
	gVal = 0;
	bVal = 0;
	rowVal = 0;
	colVal = 0;
}

bool Pixel::isWhitePixel()
{
	// Normal Value: 230, Simulation Values: 180
	if (rVal >= 230 && gVal >= 230 && bVal >= 230) {
		return true;
	}
	else {
		return false;
	}
}

bool Pixel::isRedPixel()
{
	// Normal Value: 230, Simulation Values: 180
	if (rVal >= 200 && gVal <= 100 && bVal <= 100) {
		return true;
	}
	else {
		return false;
	}
}

bool Pixel::pixelInDist(int distance, Pixel pixel)
{

	if (pixel.row() >= rowVal && pixel.row() <= (rowVal + distance)) {
		// Check row vals
		return true;
	}
	else if (pixel.row() <= rowVal && pixel.row() >= (rowVal - distance)) {
		// Check row vals
		return true;
	}
	else if (pixel.col() <= colVal && pixel.col() >= (colVal - distance)) {
		// Check col vals
		return true;
	}
	else if (pixel.col() <= colVal && pixel.col() >= (colVal - distance)) {
		// Check col vals
		return true;
	}
	return false;
}

Pixel::Pixel(QColor pixelColor, int row, int col)
{
	rVal = pixelColor.red();
	gVal = pixelColor.blue();
	bVal = pixelColor.green();
	rowVal = row;
	colVal = col;
	pixelInitialized = true;
}

Pixel::Pixel()
{
	pixelInitialized = false;
}

int Pixel::r()
{
	return rVal;
}

int Pixel::g()
{
	return gVal;
}

int Pixel::b()
{
	return bVal;
}

int Pixel::row()
{
	return rowVal;
}

int Pixel::col()
{
	return colVal;
}

bool Pixel::initialized()
{
	return pixelInitialized;
}

void Pixel::setR(int color)
{
	rVal = color;
}

void Pixel::setG(int color)
{
	gVal = color;
}

void Pixel::setB(int color)
{
	bVal = color;
}

void Pixel::setRow(int r)
{
	rowVal = r;
}

void Pixel::setCol(int c)
{
	colVal = c;
}
