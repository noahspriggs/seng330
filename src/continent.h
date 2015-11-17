#ifndef CONTINENT_H
#define  CONTINENT_H

#include "country.h"
#include <vector>

/*! A Continent is a grouping of Countrys that is taken into account when calculating income*/
class Continent {
public:
  Continent();
 
 //! Adds a pointer to a country into countries
/*!
\param country an pointer to a country that is pushed onto countries
*/
  void addCountry(Country* country);

  std::vector<Country*> countries; /*!< A vector storing all of the continent's countries */

};
#endif