#include "uimanager.h"
#include <iostream>
#include <sstream>
#include <string>

UIManager::UIManager() {
    this->mapController = new MapController();
    this->turnController = new TurnController(mapController);
    this->mapController->turnController = this->turnController;
    this->shopController = new ShopController(turnController);
	this->moveController = new MoveController(mapController);

    turnController->startGame();
	if (!this->textFont.loadFromFile("caladea-regular.ttf")) {
		std::cout << "Error loading font from caladea-regular.ttf" << std::endl;
	}

}

void UIManager::draw(sf::RenderWindow* target) 
{
    
    sf::Sprite mapSprite;
    sf::Texture tex = this->mapController->getPixels();
    mapSprite.setTexture(tex);
    
    target->draw(mapSprite);

	//draw the unit counts on the countries
	//we know where the origins are for the demo
	sf::Text unitCountText;
	unitCountText.setFont(this->textFont);
	unitCountText.setCharacterSize(24);
	unitCountText.setColor(sf::Color::Magenta);
	unitCountText.setStyle(sf::Text::Regular);

	for (int c = 0; c < this->mapController->map->getContinents().size(); c++) {
		Continent* continent = this->mapController->map->getContinents()[c];

		for (int cu = 0; cu < continent->countries.size(); cu++) {
			Country* country = continent->countries[cu];

			int xPos = country->getXPosition() + country->getCenterOffsetX();
			int yPos = country->getYPosition() + country->getCenterOffsetY();

			unitCountText.setPosition(xPos, yPos);

			std::stringstream ss;
			ss << country->getUnits();
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
        
        shopController->placeUnit(turnController->getActivePlayer(),mapController->pointToCountry(x,y));
    }
    if (turnController->phase == ACTION ) {
		moveController->handleClick(x, y, turnController->getActivePlayer() );
    }

    //std::cout << "Handled click at " << x << " " << y << std::endl;
    //std::cout << "Mapped to country p = 0x" << this->mapController->pointToCountry(x, y) << std::endl;
}