#include "shopcontroller.h"
#include <iostream>


ShopController::ShopController(TurnController* tc) {
    turnController = tc;
}

void ShopController::placeUnit(Player* placer, Country* country) {
    //eventually we will need "&& country->targetable == true"
    //which makes sure the player owns the country in the PLACE phase, but I left it out for debugging
    if (placer->income > 0) {
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