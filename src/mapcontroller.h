#ifndef MAPCONTROLLER_H
#define  MAPCONTROLLER_H

#include "map.h"
#include <SFML/Graphics.hpp>


class MapController {
public:
  MapController();

  sf::Texture getPixels();
  Country* pointToCountry(int x, int y);
  
  Map* map;
};
#endif