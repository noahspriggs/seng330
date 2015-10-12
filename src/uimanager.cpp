#include "uimanager.h"
#include <iostream>

UIManager::UIManager() {
    this->mapController = new MapController();
    this->turnController = new TurnController();
    this->shopController = new ShopController();
	this->moveController = new MoveController(mapController);
}

void UIManager::draw(sf::RenderWindow* target) 
{
    //highlight all the countries that the activeplayer owns
    if (turnController->phase == PLACE) {
        Player* placer = turnController->getActivePlayer();

        for (int i = 0; i < placer->countries.size(); i++) {
            placer->countries[i]->highlight = true;
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
    if (turnController->phase == PLACE) {
        shopController->placeUnit(turnController->getActivePlayer(),mapController->pointToCountry(x,y));
    }
    if (turnController->phase == ACTION  || true) {	// || true to ensrue we enter here otherwise we are never in action phase
		moveController->handleClick(x, y);
    }


    //std::cout << "Handled click at " << x << " " << y << std::endl;
    
    //std::cout << "Mapped to country p = 0x" << this->mapController->pointToCountry(x, y) << std::endl;
}