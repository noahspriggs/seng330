#ifndef MAP_H
#define  MAP_H

#include "continent.h"
#include <vector>


/*! Map is the class that is a map or squares which contains the information of all the continents */
class Map {
public:
	/*!<std - is a vector that is storing the new continents >*/
  std::vector<Continent*> continents;
  int width, height;
  //! Constructs a new blank 3x3 map or squares for the purposes of this demo.
  Map();

  //! returns a vector of all the continents in on the map currently
  std::vector<Continent*> getContinents();

  //!initializes the height and the width of the map
  int getWidth();
  int getHeight();

};
#endif
