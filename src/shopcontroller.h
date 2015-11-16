#ifndef SHOPCONTROLLER_H
#define  SHOPCONTROLLER_H

#include "turncontroller.h"
#include "mapcontroller.h"
#include "country.h"
#include "player.h"
#include <SFML/Graphics.hpp>

/*! ShopController is the class that controls the numbers of units that can be placed of the actived player. It does the work for counting the numbers of placing the units of the actived player. After placing the units, the player should begin to act.*/
class ShopController {
public:
    
/*!
\param tc an pointer argument used to access the TurnController
*/
  ShopController(TurnController* tc);

//! Action method, to allow actived player to place unit
/*!
\param placer an pointer to the Player who are actived player and he can place units
\param country an pointer to the actived player's counrty
*/

  void placeUnit(Player* placer, Country* country);

//! Access Method, to access the numbers of player's income.
/*!
\param player an pointer to the Player who are actived player
*/
  int getPlayerIncome(Player* player);

  MapController* mapController;/*!< A pointer to the map controller */
  TurnController* turnController;/*!< A pointer to the turn controller */


};
#endif