#ifndef MAP_H
#define  MAP_H

#include "continent.h"
#include <vector>



class Map {
public:
  Map();

  std::vector<Continent*> continents;

};
#endif