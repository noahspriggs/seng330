#include "player.h"
#include <iostream>
#include <vector>
#include <algorithm>

//!initial income of the player
Player::Player() {
    income = -1;
}

bool Player::ownsCountry(Country* country){
 	
	// Check country in countries
	if ( std::find(countries.begin(), countries.end(), country) != countries.end() ){
		//std::cout << "Player owns country" << std::endl;
		return true;
	}else {
		//std::cout << "Player does NOT own country" << std::endl;
		return false;
	}

	return false;
}
//new country is added to players collection of countries 
void Player::addCountry(Country* country){
	countries.push_back(country);
}
// a country is deleted from a player when they loose at a turn
void Player::removeCountry(Country* country){
	countries.erase(std::remove(countries.begin(), countries.end(), country), countries.end());
}



