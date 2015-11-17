#ifndef PLAYER_H
#define  PLAYER_H

#include "country.h"
#include <vector>


class Player {
public:
  Player();
//characteristics of the player
  bool ownsCountry(Country* country);
  void addCountry(Country* country);
  void removeCountry(Country* country);
  int number;
  int colour;
  int income;
  std::vector<Country*> countries;
  

};
#endif