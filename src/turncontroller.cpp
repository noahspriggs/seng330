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
    if(!mapController->loadMap()) {
        playerList[0]->addCountry(mapController->map->getContinents()[0]->countries[0]);
        mapController->map->getContinents()[0]->countries[0]->setUnits(1);
        playerList[1]->addCountry(mapController->map->getContinents()[2]->countries[2]);
        mapController->map->getContinents()[2]->countries[2]->setUnits(1);
        mapController->update();
    } else {
        mapController->update();
    }

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
