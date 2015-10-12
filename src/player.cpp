#include "player.h"
#include <iostream>
#include <vector>
#include <algorithm>

Player::Player() {

}

bool Player::ownsCountry(Country* country1){
 	
	// Check country in countries
	if ( std::find(this->countries.begin(), this->countries.end(), country1) != this->countries.end() ){
		std::cout << "Player owns country" << std::endl;
		return true;
	}else {
		std::cout << "Player does NOT own country" << std::endl;
		return false;
	}

	return false;
}
 
 

