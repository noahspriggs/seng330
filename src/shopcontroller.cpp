#include "shopcontroller.h"
#include <iostream>


ShopController::ShopController(TurnController* tc) {
    turnController = tc;
}

void ShopController::placeUnit(Player* placer, Country* country) {
    Player* activePlayer = turnController->getActivePlayer();
    //if the income is -1 then turncontroller just reset the turn so we need a new income
    if(activePlayer->income == -1) {
        activePlayer->income = getPlayerIncome(activePlayer);
    }

    if (placer->income > 0 && placer->ownsCountry(country)) {
        country->units++;
        placer->income--;
        
		if (placer->income == 0) {
            turnController->phase = ACTION;
            std::cout << "BEGINNING ACTION PHASE" << std::endl;
        }
    } else {
        std::cout << "not your country" << std::endl;
    }
}

int ShopController::getPlayerIncome(Player* player) {
    return player->countries.size() + 3;
}