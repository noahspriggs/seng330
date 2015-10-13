#include "turncontroller.h"
#include <iostream>


TurnController::TurnController(MapController* mc) {
    mapController = mc;

    playerList.push_back(new Player());
    playerList.push_back(new Player());

    activePlayer = 0;
    phase = PLACE;
}

void TurnController::startGame() {
    playerList[0]->countries.push_back(mapController->map->getContinents()[0]->countries[0]);
    playerList[1]->countries.push_back(mapController->map->getContinents()[2]->countries[2]);
}

void TurnController::endTurn() {
    activePlayer = (activePlayer + 1) % playerList.size();
    phase = PLACE;

    //set player income to -1 to indicate that it needs to be recalculated
    playerList[activePlayer]->income = -1;
} 

Player* TurnController::getActivePlayer() {
    return playerList[activePlayer];
}