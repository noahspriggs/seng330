#include "movecontroller.h"
#include <iostream>

MoveController::MoveController(MapController* mapController) {
    this->mapController =  mapController;
	this->arrowsDisplayed = false;
	this->country = NULL;
}

void MoveController::draw(sf::RenderWindow* target) 
{

// Draw arrows 
    sf::Sprite mapSprite;
    sf::Texture tex = this->mapController->getPixels();
    mapSprite.setTexture(tex);
    
    target->draw(mapSprite);
}
  
void MoveController::handleClick(int x, int y)
{
	Country * clicked = this->mapController->pointToCountry(x, y);

	if ( country == NULL ){
		country = clicked;
		arrowsDisplayed = true;
		 std::cout << "Selected New Country" << std::endl;
	} else if ( !arrowsDisplayed )  {
		country = clicked;
		arrowsDisplayed = true;
		std::cout << "Selected New Country" << std::endl;
		
		
	} else if ( arrowsDisplayed && clicked == country ){
		std::cout << "DE-Selected Country" << std::endl;
		arrowsDisplayed = false;
		
	}else if ( arrowsDisplayed && clicked != country){
		std::cout << "handleMove" << std::endl;
		handleMove(country, clicked);
	}
	
}


bool MoveController::handleArrowClick(int x, int y){
	return false;
}

void MoveController::handleMove(Country * country1, Country* country2){

	// Check country's are adjacent
	if ( std::find(country1->neighbours.begin(), country1->neighbours.end(), country2) != country1->neighbours.end() ){
		std::cout << "Countries are adjacent" << std::endl;
	}else {
		std::cout << "Countries are not adjacent. Handle Move failed" << std::endl;
		return;
	}
		

	// Merge
	// if current player owns 2
		handleMerge(country1, country2);
		
	// Attack
	// if player does not own 2
		handleAttack(country1, country2);

}

void MoveController::handleMerge(Country * country1, Country* country2){


	
}

void MoveController::handleAttack(Country * country1, Country* country2){
	
}

