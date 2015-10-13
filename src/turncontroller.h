#ifndef TURNCONTROLLER_H
#define  TURNCONTROLLER_H

#include "mapcontroller.h"
#include "country.h"
#include "player.h"
#include <SFML/Graphics.hpp>

enum Phases { MENU, SHOP, PLACE, ACTION };


class TurnController {
public:
  TurnController(MapController* mc);

  void startGame();
  void endTurn();

  Player* getActivePlayer();

  int phase;

  int activePlayer;
  std::vector<Player*> playerList;

  MapController* mapController;

};
#endif