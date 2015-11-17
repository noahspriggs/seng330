#ifndef COUNTRY_H
#define  COUNTRY_H

#include <vector>

//!creates a country with given width,height, units, position  
class Country
{
public:
 //! sets up the size, the positon and units in the game with set X and Y   
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
//! adds neighbour besides the country
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
