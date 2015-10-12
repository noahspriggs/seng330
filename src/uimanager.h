#ifndef UIMANAGER_H
#define  UIMANAGER_H

#include "mapcontroller.h"
#include <SFML/Graphics.hpp>


class UIManager {
  MapController* mapController;
public:
  UIManager();
  
  void draw(sf::RenderWindow* target);
  
  void handleClick(int x, int y);

};
#endif