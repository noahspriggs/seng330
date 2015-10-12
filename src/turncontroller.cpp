#include "turncontroller.h"
#include <iostream>


TurnController::TurnController() {
    playerList.push_back(new Player());
    playerList.push_back(new Player());

    activePlayer = 0;
    phase = PLACE;
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