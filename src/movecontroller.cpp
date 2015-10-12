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
  
void MoveController::handleClick(int x, int y, Player * player)
{
	Country * clicked = this->mapController->pointToCountry(x, y);

	if ( country == NULL && player->ownsCountry(clicked)  ){
		country = clicked;
		arrowsDisplayed = true;
		 std::cout << "Selected New Country" << std::endl;
	} else if ( !arrowsDisplayed && player->ownsCountry(clicked) )  {
	
		country = clicked;
		arrowsDisplayed = true;
		std::cout << "Selected New Country" << std::endl;
		
		
	} else if ( arrowsDisplayed && clicked == country ){
		std::cout << "DE-Selected Country" << std::endl;
		arrowsDisplayed = false;
		country = NULL;
		
	}else if ( arrowsDisplayed && clicked != country){
		std::cout << "handleMove" << std::endl;
		handleMove(country, clicked, player);
	}
	
}


bool MoveController::handleArrowClick(int x, int y){
	return false;
}

void MoveController::handleMove(Country * country1, Country* country2, Player * player){

	// Check country's are adjacent
	if ( std::find(country1->neighbours.begin(), country1->neighbours.end(), country2) != country1->neighbours.end() ){
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
		handleAttack(country1, country2);	
	}
}

void MoveController::handleMerge(Country * country1, Country* country2){


	
}

void MoveController::handleAttack(Country * country1, Country* country2){
	
}

