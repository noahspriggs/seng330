#ifndef TURNCONTROLLER_H
#define  TURNCONTROLLER_H

#include "mapcontroller.h"
#include "country.h"
#include "player.h"
#include <SFML/Graphics.hpp>

enum Phases { MENU, SHOP, PLACE, ACTION }; /*!< Enumerated phases of the game. */


/*! TurnController is the class that controls which player is currently playing, and what phases the game is in.*/
class TurnController {
public:

//! Creation Method taking two arguments
/*!
\param mc an pointer argument used to access the MapController
*/
  TurnController(MapController* mc);

  //! Sets up the game, assigning Player's their initial Countries and
  void startGame();
  
  //! Ends the activePlayer turn, and begins the next players.
  void endTurn();

//! Access Method, used by outside classes to get identify the active player.
/*!
\return a pointer to the active Player 
*/
  Player* getActivePlayer(); 

  int phase; /*!< An integer storing the game's current phase */

  int activePlayer; /*!< An integer storing the game's activePlayer's index */
  std::vector<Player*> playerList;  /*!< A vector storing the game's Players */

  MapController* mapController; /*!< An point to MapController used for access */

};
#endif