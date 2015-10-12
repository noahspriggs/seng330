#ifndef PLAYER_H
#define  PLAYER_H

#include "country.h"
#include <vector>


class Player {
public:
  Player();

  bool ownsCountry(Country* country1);
  
  int number;
  int colour;
  int income;
  std::vector<Country*> countries;
  

};
#endif