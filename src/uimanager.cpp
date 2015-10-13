#include "uimanager.h"
#include <iostream>
#include <sstream>
#include <string>

UIManager::UIManager() {
    this->mapController = new MapController();
    this->turnController = new TurnController();
    this->shopController = new ShopController(turnController);
	this->moveController = new MoveController(mapController);

	if (!this->textFont.loadFromFile("caladea-regular.ttf")) {
		std::cout << "Error loading font from caladea-regular.ttf" << std::endl;
	}

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

	//draw the unit counts on the countries
	//we know where the origins are for the demo
	sf::Text unitCountText;
	unitCountText.setFont(this->textFont);
	unitCountText.setCharacterSize(24);
	unitCountText.setColor(sf::Color::Black);
	unitCountText.setStyle(sf::Text::Regular);

	for (int c = 0; c < this->mapController->map->getContinents().size(); c++) {
		Continent* continent = this->mapController->map->getContinents()[c];

		for (int cu = 0; cu < continent->countries.size(); cu++) {
			Country* country = continent->countries[cu];

			int xPos = country->xPosition + country->centerOffsetX;
			int yPos = country->yPosition + country->centerOffsetY;

			unitCountText.setPosition(xPos, yPos);

			std::stringstream ss;
			ss << country->units;
			unitCountText.setString(ss.str().c_str());

			target->draw(unitCountText);
		}
	}
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