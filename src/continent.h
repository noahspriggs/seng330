#ifndef CONTINENT_H
#define  CONTINENT_H

#include "country.h"
#include <vector>

//! Continent is the class that adds a country 
class Continent {
public:

  Continent();
  
  void addCountry(Country* country); /*!<this adds a new country>*/

  std::vector<Country*> countries; /*! <a vector storing the country>*/

};
#endif