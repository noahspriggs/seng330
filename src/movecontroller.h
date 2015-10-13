#ifndef MOVECONTROLLER_H
#define  MOVECONTROLLER_H

#include "mapcontroller.h"
#include "turncontroller.h"
#include "player.h"
#include <SFML/Graphics.hpp>


class MoveController {
  MapController* mapController;
  TurnController* turnController;
public:
  MoveController(MapController* mapController, TurnController* tc);
  
  void draw(sf::RenderWindow* target);
  
  void handleClick(int x, int y, Player * player);
  
 private: 
 
	bool handleArrowClick(int x, int y);
	void handleMove(Country * country1, Country* country2,Player * player);
	void handleMerge(Country * country1, Country* country2);
	void handleAttack(Country * country1, Country* country2, Player* player);

 
 
 
	bool arrowsDisplayed;
	Country * country;


};
#endif