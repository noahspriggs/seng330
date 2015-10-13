#ifndef UIMANAGER_H
#define  UIMANAGER_H

#include "mapcontroller.h"
#include "turncontroller.h"
#include "shopcontroller.h"
#include "movecontroller.h"
#include <SFML/Graphics.hpp>


class UIManager {
  MapController* mapController;
  TurnController* turnController;
  ShopController* shopController;
  MoveController* moveController;

  sf::Font textFont;

public:

  UIManager();
  
  void draw(sf::RenderWindow* target);
  
  void handleClick(int x, int y);

};
#endif