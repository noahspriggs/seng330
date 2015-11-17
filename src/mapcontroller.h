#ifndef MAPCONTROLLER_H
#define  MAPCONTROLLER_H

#include "json.h"
#include "map.h"
#include <SFML/Graphics.hpp>


class TurnController;

class MapController {
public:
  MapController();

  void update();
  sf::Texture getPixels();
  Country* pointToCountry(int x, int y);
  sf::Texture getMapTexture();
  bool loadMap();
  void saveMap();

  sf::Texture mapTexture;
  Map* map;
  TurnController* turnController;
};
#endif
