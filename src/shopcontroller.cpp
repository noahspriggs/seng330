#include "shopcontroller.h"



ShopController::ShopController() {

}

void ShopController::placeUnit(Player* placer, Country* country) {
    if (placer->income > 0) {
        country->units++;
    } else {
        turnController->phase++;
    }
}

int ShopController::getPlayerIncome(Player* player) {
    return player->countries.size();
}