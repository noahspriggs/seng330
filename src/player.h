#ifndef PLAYER_H
#define  PLAYER_H

#include "country.h"
#include <vector>

/*!This is a player class which shows if the player who is playing own a country,
added/ removed a country after their turn, the income a player has, colour, number of player
*/
class Player {
public:
  Player();
//characteristics of the player
/*! the country which is owned by a player*/
  bool ownsCountry(Country* country);
 /*!calls the method addCountry to add another country to
   current players collection if they won at a turn*/ 
  void addCountry(Country* country);
  /*!calls removeCountry to remove a country after current player looses
     at a turn*/
  void removeCountry(Country* country);
  int number;
  int colour;
  //! the income of a player while/ after the game
  int income;
  std::vector<Country*> countries;
  

};
#endif