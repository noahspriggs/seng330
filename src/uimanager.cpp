#include "uimanager.h"
#include <iostream>

UIManager::UIManager() {
    this->mapController = new MapController();
    this->turnController = new TurnController(mapController);
    this->shopController = new ShopController(turnController);
	this->moveController = new MoveController(mapController);

    turnController->startGame();

}

void UIManager::draw(sf::RenderWindow* target) 
{
    //highlight all the countries that the activeplayer owns
    if (turnController->phase == PLACE) {
        Player* placer = turnController->getActivePlayer();

        for (int i = 0; i < placer->countries.size(); i++) {
            placer->countries[i]->targetable = true;
        }
    }
    sf::Sprite mapSprite;
    sf::Texture tex = this->mapController->getPixels();
    mapSprite.setTexture(tex);
    
    target->draw(mapSprite);
}
  
void UIManager::handleClick(int x, int y)
{
    //depending on the current turn phase, do different things on mouse click
    Player* activePlayer = turnController->getActivePlayer();
    if (turnController->phase == PLACE) {
        //if the income is -1 then turncontroller just reset the turn so we need a new income
        if(activePlayer->income == -1) {
            activePlayer->income = shopController->getPlayerIncome(activePlayer);
        }
        shopController->placeUnit(turnController->getActivePlayer(),mapController->pointToCountry(x,y));
    }
    if (turnController->phase == ACTION ) {
		moveController->handleClick(x, y, turnController->getActivePlayer() );
    }

    //std::cout << "Handled click at " << x << " " << y << std::endl;
    //std::cout << "Mapped to country p = 0x" << this->mapController->pointToCountry(x, y) << std::endl;
}