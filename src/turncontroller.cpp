#include "turncontroller.h"
#include <iostream>


TurnController::TurnController() {
    playerList.push_back(new Player());
    playerList.push_back(new Player());

    activePlayer = 0;
}

void TurnController::endTurn() {
    activePlayer = (activePlayer + 1) % playerList.size();
    phase = PLACE;
} 

Player* TurnController::getActivePlayer() {
    return playerList[activePlayer];
}