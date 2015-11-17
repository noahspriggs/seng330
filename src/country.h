#ifndef COUNTRY_H
#define  COUNTRY_H

#include <vector>

//! country is the smallest unit chunk of the map. They are given width,height, units, position , Are owned by players.
class Country
{
public:

  int width;
  int height;
  int* mask;
  int units;

  int xPosition;
  int yPosition;

  int centerOffsetX;
  int centerOffsetY;

  std::vector<Country*> neighbours;

  Country();
  Country(int width, int height, int* mask, int xPosition, int yPosition, int centerOffsetX, int centerOffsetY);

  void addNeighbour(Country* neighbour);
  std::vector<Country*> getNeighbours();

  int getWidth();
  int getHeight();

  int* getMask();


  int getUnits();
  void setUnits(int units);

  int getXPosition();
  int getYPosition();

  int getCenterOffsetX();
  int getCenterOffsetY();

};
#endif
