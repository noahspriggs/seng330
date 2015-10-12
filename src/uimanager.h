#ifndef UIMANAGER_H
#define  UIMANAGER_H

#include "mapcontroller.h"
#include "turncontroller.h"
#include "shopcontroller.h"
#include <SFML/Graphics.hpp>


class UIManager {
  MapController* mapController;
  TurnController* turnController;
  ShopController* shopController;
public:
  enum { MENU, SHOP, PLACE, ACTION };

  UIManager();
  
  void draw(sf::RenderWindow* target);
  
  void handleClick(int x, int y);

};
#endif