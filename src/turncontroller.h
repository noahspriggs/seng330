#ifndef TURNCONTROLLER_H
#define  TURNCONTROLLER_H

#include "mapcontroller.h"
#include "country.h"
#include "player.h"
#include <SFML/Graphics.hpp>


class TurnController {
public:
  TurnController();

  void endTurn();

  Player* getActivePlayer();

  enum { MENU, SHOP, PLACE, ACTION };
  int phase;

  int activePlayer;
  std::vector<Player*> playerList;

};
#endif