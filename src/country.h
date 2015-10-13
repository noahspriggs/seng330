#ifndef COUNTRY_H
#define  COUNTRY_H

#include <vector>


class Country {
public:
  Country();

  void addNeighbour(Country* neighbour);
 
  int width;
  int height;
  int* mask;
  int units;

  int xPosition;
  int yPosition;
  
  int centerOffsetX;
  int centerOffsetY;
  
  std::vector<Country*> neighbours;
};
#endif