#ifndef MAP_H
#define  MAP_H

#include "continent.h"
#include <vector>



class Map {
public:
  std::vector<Continent*> continents;
  int width, height;
  // Constructs a new blank 3x3 map or squares for the purposes of this demo.
  Map();

  // returns a vector of all the continents in on the map currently
  std::vector<Continent*> getContinents();

  int getWidth();
  int getHeight();

};
#endif
