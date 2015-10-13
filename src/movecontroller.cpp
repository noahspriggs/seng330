#include "movecontroller.h"
#include <iostream>

MoveController::MoveController(MapController* mapController) {
    this->mapController =  mapController;
	this->arrowsDisplayed = false;
	this->country = NULL;
}


// TODO add graphical interface
void MoveController::draw(sf::RenderWindow* target)
{
// Draw arrows
    sf::Sprite mapSprite;
    sf::Texture tex = this->mapController->getPixels();
    mapSprite.setTexture(tex);

    target->draw(mapSprite);
}

void MoveController::handleClick(int x, int y, Player * player)
{
	Country * clicked = this->mapController->pointToCountry(x, y);

	//Case: No Current country selected, select country if player owns
	if ( country == NULL && player->ownsCountry(clicked)  ){
		country = clicked;
		arrowsDisplayed = true;
		 std::cout << "Selected New Country" << std::endl;

	//Case: No Current country selected, select country if player owns
	} else if ( !arrowsDisplayed && player->ownsCountry(clicked) )  {

		country = clicked;
		arrowsDisplayed = true;
		std::cout << "Selected New Country" << std::endl;

	//Case: UN-Select selected country
	} else if ( arrowsDisplayed && clicked == country ){
		std::cout << "DE-Selected Country" << std::endl;
		arrowsDisplayed = false;
		country = NULL;

	//Case: Selected country not the same as clicked: IE could be a merge or an attack
	}else if ( arrowsDisplayed && clicked != country){
		std::cout << "handleMove" << std::endl;
		handleMove(country, clicked, player);
	}else {
		std::cout << "Select A country you own to Move your units" << std::endl;
	}




}


bool MoveController::handleArrowClick(int x, int y){
	return false;
}

void MoveController::handleMove(Country * country1, Country* country2, Player * player){

	// Check country's are adjacent
	std::vector<Country*> country1Neighbours = country1->getNeighbours();

	if ( std::find(country1Neighbours.begin(), country1Neighbours.end(), country2) != country1Neighbours.end() ){
		std::cout << "Countries are adjacent: move possible" << std::endl;
	}else {
		std::cout << "Countries are not adjacent: Move NOT possible" << std::endl;
		return;
	}


	if ( player->ownsCountry(country2) ){	//if current player owns 2

		// Merge
		handleMerge(country1, country2);

	} else {	//  player does not own 2

		// Attack
		handleAttack(country1, country2, player);
	}
}

void MoveController::handleMerge(Country * country1, Country* country2){

	//For phase2 Disallow moving last unit from a country
	//For phase2 moves all but last unit
	if ( country1->getUnits() > 1) {
		country2->setUnits(country1->getUnits() - 1);
		std::cout << "Moved " << country1->getUnits() - 1 << " units"  << std::endl;

		country1->setUnits(1);


	}else {
		std::cout << "To Few units to move" << std::endl;
	}
}

void MoveController::handleAttack(Country * country1, Country* country2, Player* player){

	//For phase2 Disallow moving last unit from a country
	//For phase2 moves all but last unit
	//For phase2 only allow attack if you will window
	//For phase2 its 1-1 kill ratio

	if ( country1->getUnits() > 1 && country1->getUnits() - 1 > country2->getUnits()) {

		country1->setUnits(country1->getUnits() - country2->getUnits());
		country2->setUnits(country1->getUnits() - 1);

		std::cout << "Attack succeeded moved " << country2->getUnits() << " into your new country" << std::endl;

		// ----REMOVE Country2 from previous owner-----
		//TODO find owner of (country2)   otherPlayer.removeCountry(country2);

		// -- Add Country ownership to player --
		player->addCountry(country2);

		country1->setUnits(1);

	}else {
		std::cout << "To Few units to attack" << std::endl;
	}



}

