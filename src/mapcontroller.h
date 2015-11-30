#ifndef MAPCONTROLLER_H
#define  MAPCONTROLLER_H

#include "json.h"
#include "map.h"
#include <SFML/Graphics.hpp>


class TurnController; /*! used to access the TurnController*/
class MoveController; /*! used to access the MoveController*/

/*! MapController is the class that updates the */
class MapController {
public:
  std::vector<sf::Color> playerColours;

  MapController();
  //! updates the game once it starts or is restarted
    void update();
	sf::Texture getPixels();

  //! call the country class and points to the country on the maps
  Country* pointToCountry(int x, int y);

  sf::Texture getMapTexture();
  bool loadMap();
  //! saved the map that is created for each news game
  void saveMap();

  sf::Texture mapTexture;
  Map* map; /*!<an pointer to Map used for access>*/
  TurnController* turnController; /*!<an pointer to TurnController used for access>*/
  MoveController* moveController;
};
#endif
