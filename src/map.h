#ifndef MAP_H
#define  MAP_H

#include "continent.h"
#include <vector>


/*! Map is the class that is a map or squares which contains the information of all the continents */
class Map {
	unsigned long long seed;
	double* currentFbm = 0;
	int* countryMap = 0;
	bool* isBorder = 0;
	bool* isSealane = 0;
	Country** countries = 0;

public:
	/*!<std - is a vector that is storing the new continents >*/
  std::vector<Continent*> continents;
  int width, height;
  //! Constructs a new map from the specified seed
  //! \param seed The seed to generate the map from.
  Map(unsigned long long seed);
  virtual ~Map();

  //! returns a vector of all the continents in on the map currently
  std::vector<Continent*> getContinents();

  //!initializes the height and the width of the map
  int getWidth();
  int getHeight();

  //! is the given point on land
  bool isPointOnLand(int x, int y);

  //! is the given point on a border between two countries
  //! could be in the water
  bool isPointBorder(int x, int y);

  //! is this point on a sealane
  bool isPointSealane(int x, int y);

  //! Returns the random seed of this map
  unsigned long long getSeed();

  //! Generates the corresponding Fractal Brownian Motion for
  //! the current seed.
  double* getFBM();

  //! Gets the pixel-by-pixel breakdown of country pixel positioning
  int* getCountryMap();

  //! Gets the country that maps from pixel ownership from getCountryMap
  //! \param id The id from getCountryMap
  Country* getCountryById(int id);

  //! Gets the total number of countries
  int getNumCountries();

};
#endif
