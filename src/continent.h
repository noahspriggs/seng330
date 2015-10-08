#ifndef CONTINENT_H
#define  CONTINENT_H

#include "country.h"
#include <vector>
class Continent {
public:
  Continent();

  std::vector<Country*> countries;

};
#endif