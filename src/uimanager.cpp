#include "uimanager.h"
#include <iostream>
#include <sstream>
#include <string>

UIManager::UIManager() {
    this->mapController = new MapController();
    this->mapController->playerColours.push_back(sf::Color(255,0,0));
    this->mapController->playerColours.push_back(sf::Color(0,255,0));
	this->turnController = new TurnController(mapController);
    this->mapController->turnController = this->turnController;
    this->shopController = new ShopController(turnController);
	this->moveController = new MoveController(mapController,turnController);
	turnController->startGame();

	if (!this->textFont.loadFromFile("caladea-regular.ttf")) {
		std::cout << "Error loading font from caladea-regular.ttf" << std::endl;
	}
}

void UIManager::draw(sf::RenderWindow* target)
{

    sf::Sprite mapSprite;
    // this->mapController->update();
    sf::Texture tex = this->mapController->getMapTexture();
    mapSprite.setTexture(tex);
    mapSprite.setPosition(xincrease,yincrease);

    target->draw(mapSprite);

	//draw the unit counts on the countries
	//we know where the origins are for the demo
	sf::Text unitCountText;
	unitCountText.setFont(this->textFont);
	unitCountText.setCharacterSize(24);
	unitCountText.setColor(sf::Color::Magenta);
	unitCountText.setStyle(sf::Text::Regular);

    //draw unit counts on countries
	for (int c = 0; c < this->mapController->map->getContinents().size(); c++) {
		Continent* continent = this->mapController->map->getContinents()[c];

		for (int cu = 0; cu < continent->countries.size(); cu++) {
			Country* country = continent->countries[cu];

			int xPos = country->getXPosition() + xincrease + country->getCenterOffsetX();
			int yPos = country->getYPosition() + yincrease + country->getCenterOffsetY();

			unitCountText.setPosition(xPos, yPos);

			std::stringstream ss;
			ss << country->getUnits();
			unitCountText.setString(ss.str().c_str());

			target->draw(unitCountText);
		}
	}

    //draw ui information

    for(int i = 0; i < 2; i++) {
        sf::Color c = mapController->playerColours[i];

        if(turnController->activePlayer != i) {
            c.r += 30;
            c.g += 30;
            c.b += 30;
        }
        unitCountText.setColor(c);
        unitCountText.setCharacterSize(46);
        int x = (i*(900+xincrease)+xincrease/2-80);
        std::stringstream uistring;
        uistring << "Player " << i+1;
        unitCountText.setString(uistring.str().c_str());
        unitCountText.setPosition(x,yincrease);
        target->draw(unitCountText);

        unitCountText.setCharacterSize(33);
        unitCountText.setPosition(x,yincrease+50);
        std::stringstream incomestring;
            incomestring << "Income: " << shopController->getPlayerIncome(turnController->playerList[i]);


        unitCountText.setString(incomestring.str().c_str());

        target->draw(unitCountText);

        unitCountText.setPosition(x,yincrease+100);
        std::stringstream unitstream;
        if(turnController->playerList[i]->income == -1) {
            unitstream << "Stored Units: " << 0;
        } else {
            unitstream << "Stored Units: " << turnController->playerList[i]->income;
        }
        unitCountText.setString(unitstream.str().c_str());

        target->draw(unitCountText);
    }




}

void UIManager::handleClick(int x, int y)
{
    // mapController->update();
    //depending on the current turn phase, do different things on mouse click
    Player* activePlayer = turnController->getActivePlayer();
    if (turnController->phase == PLACE) {

        shopController->placeUnit(turnController->getActivePlayer(),mapController->pointToCountry(x-xincrease,y-yincrease));
    }
    if (turnController->phase == ACTION ) {
		moveController->handleClick(x-xincrease, y-yincrease, turnController->getActivePlayer() );
    }

    //std::cout << "Handled click at " << x << " " << y << std::endl;
    //std::cout << "Mapped to country p = 0x" << this->mapController->pointToCountry(x, y) << std::endl;
}

void UIManager::handleEsc() {
    turnController->endTurn();
}

void UIManager::save() {
    mapController->saveMap();
}
