#ifndef CONTINENT_H
#define  CONTINENT_H

#include "country.h"
#include <vector>

<<<<<<< HEAD
//! Continent is the class that adds a country 
=======
/*! A Continent is a grouping of Countrys that is taken into account when calculating income*/
>>>>>>> 24af3daba1bd3c23c5ba5a599e4e5c953a4fcbb8
class Continent {
public:

  Continent();
<<<<<<< HEAD
  
  void addCountry(Country* country); /*!<this adds a new country>*/

  std::vector<Country*> countries; /*! <a vector storing the country>*/
=======
 
 //! Adds a pointer to a country into countries
/*!
\param country an pointer to a country that is pushed onto countries
*/
  void addCountry(Country* country);

  std::vector<Country*> countries; /*!< A vector storing all of the continent's countries */
>>>>>>> 24af3daba1bd3c23c5ba5a599e4e5c953a4fcbb8

};
#endif