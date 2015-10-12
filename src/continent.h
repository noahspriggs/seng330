#ifndef CONTINENT_H
#define  CONTINENT_H

#include "country.h"
#include <vector>
class Continent {
public:
  Continent();
  
  void addCountry(Country* country);

  std::vector<Country*> countries;

};
#endif