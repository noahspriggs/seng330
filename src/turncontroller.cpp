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
        for(int i = 0; i<mapController->map->continents.size();i++) {
            for(int j = 0; j<mapController->map->continents[i]->countries.size();j++) {
                Country* cur = mapController->map->continents[i]->countries[j];
                std::cout << cur->units;
            }
            std::cout << std::endl;
        }
        for(int i = 0; i<playerList.size();i++) {
            std::cout << "player " << i << ", num units owned: ";
            for(int j = 0; j<playerList[i]->countries.size();j++) {
                Country* cur = playerList[i]->countries[j];
                std::cout << cur->units;
            }
            std::cout << std::endl;

        }
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
