#include "player.h"
#include <iostream>
#include <vector>
#include <algorithm>

Player::Player() {
    income = -1;
}

bool Player::ownsCountry(Country* country1){
 	
	// Check country in countries
	if ( std::find(countries.begin(), countries.end(), country1) != countries.end() ){
		//std::cout << "Player owns country" << std::endl;
		return true;
	}else {
		//std::cout << "Player does NOT own country" << std::endl;
		return false;
	}

	return false;
}

void Player::addCountry(Country* country){
	countries.push_back(country);
}

void Player::removeCountry(Country* country){

}



