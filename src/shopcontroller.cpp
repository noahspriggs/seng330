#include "shopcontroller.h"



ShopController::ShopController() {

}

void ShopController::placeUnit(Country* country) {
    country->units++;
}

int ShopController::getPlayerIncome(Player* player) {
    return player->countries.size();
}