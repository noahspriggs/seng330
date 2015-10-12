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
  
  //useful for determining if a country should be clickable
  bool targetable;

  std::vector<Country*> neighbours;
};
#endif