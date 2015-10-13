#ifndef SHOPCONTROLLER_H
#define  SHOPCONTROLLER_H

#include "turncontroller.h"
#include "mapcontroller.h"
#include "country.h"
#include "player.h"
#include <SFML/Graphics.hpp>


class ShopController {
public:
  ShopController(TurnController* tc);

  void placeUnit(Player* placer, Country* country);

  int getPlayerIncome(Player* player);

  MapController* mapController;
  TurnController* turnController;



};
#endif