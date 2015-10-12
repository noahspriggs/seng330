#ifndef MOVECONTROLLER_H
#define  MOVECONTROLLER_H

#include "mapcontroller.h"
#include <SFML/Graphics.hpp>


class MoveController {
  MapController* mapController;
public:
  MoveController(MapController* mapController);
  
  void draw(sf::RenderWindow* target);
  
  void handleClick(int x, int y);
  
 private: 
 
	bool handleArrowClick(int x, int y);
	void handleMove(Country * country1, Country* country2);
	void handleMerge(Country * country1, Country* country2);
	void handleAttack(Country * country1, Country* country2);

 
 
 
	bool arrowsDisplayed;
	Country * country;

};
#endif