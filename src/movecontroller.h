#ifndef MOVECONTROLLER_H
#define  MOVECONTROLLER_H

#include "mapcontroller.h"
#include "turncontroller.h"
#include "player.h"
#include <SFML/Graphics.hpp>

/*! MoveController is the class that controls movement functionality. It does the work for moving an army to an adjacent country. This includes handling attacks and merges.*/
class MoveController {
  MapController* mapController; /*!< A pointer to the map controller */
  TurnController* turnController;/*!< A pointer to the turn controller */
public:

//! Creation Method taking two arguments
/*!
\param mapController an pointer argument used to access the MapController
\param tc an pointer argument used to access the TurnController
*/
  MoveController(MapController* mapController, TurnController* tc);
  
//! CURRENTLY UNUSED, method may be used in the future to allow MoveController to update the RenderWindow
/*!
\param target an pointer argument may be used to access the RenderWindow
*/
  void draw(sf::RenderWindow* target);
  
//! Action method, handles user input
/*!
\param x an integer point on the x-axis of a user click
\param y an integer point on the y-axis of a user click
\param player an pointer to the Player who did the click
*/
  void handleClick(int x, int y, Player * player);
  
 private: 
 
//! Action method, sub-set of handleClick, this method handles moving an army from one Country to another
/*!
\param country1 an pointer to the army's origin Country
\param country2 an pointer to the army's destination Country
\param player an pointer to the Player who did the action
*/
	void handleMove(Country * country1, Country* country2,Player * player);
	
//! Action method, sub-set of handleClick, this method handles merging an army from one Country to another
/*!
\param country1 an pointer to the army's origin Country
\param country2 an pointer to the army's destination Country
*/
	void handleMerge(Country * country1, Country* country2);
	
//! Action method, sub-set of handleClick, this method handles moving an army from one Country to attack another
/*!
\param country1 an pointer to the army's origin Country
\param country2 an pointer to the army's destination Country
\param player an pointer to the Player who did the action
*/
	void handleAttack(Country * country1, Country* country2, Player* player);
	
//! deSelects the currently selected Country
	void deSelect();
 
 
 
	bool arrowsDisplayed; /*!< A bool indicating a country is selected */
	Country * country;    /*!< A pointer to the selected country */


};
#endif