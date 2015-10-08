#ifndef PLAYER_H
#define  PLAYER_H

#include "country.h"
#include <vector>


class Player {
public:
  Player();

  int number;
  int colour;
  std::vector<Country*> countries;

};
#endif