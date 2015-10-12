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
  bool highlight;
  std::vector<Country*> neighbours;
};
#endif