#ifndef UIMANAGER_H
#define  UIMANAGER_H

#include "mapcontroller.h"
#include "turncontroller.h"
#include "shopcontroller.h"
#include "movecontroller.h"
#include <SFML/Graphics.hpp>

/*! UIManage is the class that controls all other controllers.*/
class UIManager {
  MapController* mapController;/*!< A pointer to the map controller */
  TurnController* turnController;/*!< A pointer to the turn controller */
  ShopController* shopController;/*!< A pointer to the shop controller */
  MoveController* moveController;/*!< A pointer to the move controller */

  sf::Font textFont;/*!< Declare a new font */
    
public:
    
  UIManager();
  
//! Draw a drawable RenderWindow
/*!
\param target an pointer argument may be used to access the RenderWindow
*/
  void draw(sf::RenderWindow* target);
  
//! Action method, handles user input
/*!
\param x an integer point on the x-axis of a user click
\param y an integer point on the y-axis of a user click
*/
  void handleClick(int x, int y);
    
//! Action method, handles user exit. After user click esc, the program will exit
  void handleEsc();
};
#endif