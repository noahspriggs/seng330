#ifndef SHOPCONTROLLER_H
#define  SHOPCONTROLLER_H

#include "mapcontroller.h"
#include "country.h"
#include "player.h"
#include <SFML/Graphics.hpp>


class ShopController {
public:
  ShopController();

  void placeUnit(Country* country);

  int getPlayerIncome(Player* player);

  MapController* mapcontroller;

};
#endif