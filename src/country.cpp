#include "country.h"

Country::Country() {
	
}

Country::Country(int width, int height, int* mask, int xPosition, int yPosition, int centerOffsetX, int centerOffsetY)
{
	this->width = width;
	this->height = height;
	this->mask = mask;

	this->xPosition = xPosition;
	this->yPosition = yPosition;

	this->centerOffsetX = centerOffsetX;
	this->centerOffsetY = centerOffsetY;

    this->units = 0;
}

void Country::addNeighbour(Country* neighbour)
{
    this->neighbours.push_back(neighbour);
}

std::vector<Country*> Country::getNeighbours()
{
	return this->neighbours;
}

int Country::getWidth()
{
	return this->width;
}

int Country::getHeight()
{
	return this->height;
}

int* Country::getMask()
{
	return this->mask;
}

int Country::getUnits()
{
	return this->units;
}

void Country::setUnits(int units)
{
	this->units = units;
}

int Country::getXPosition()
{
	return this->xPosition;
}

int Country::getYPosition()
{
	return this->yPosition;
}

int Country::getCenterOffsetX()
{
	return this->centerOffsetX;
}

int Country::getCenterOffsetY()
{
	return this->centerOffsetY;
}
