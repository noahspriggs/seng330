#include "uimanager.h"
#include <iostream>

UIManager::UIManager() {
    this->mapController = new MapController();
}

void UIManager::draw(sf::RenderWindow* target) 
{
    sf::Sprite mapSprite;
    sf::Texture tex = this->mapController->getPixels();
    mapSprite.setTexture(tex);
    
    target->draw(mapSprite);
}
  
void UIManager::handleClick(int x, int y)
{
    std::cout << "Handled click at " << x << " " << y << std::endl;
    
    std::cout << "Mapped to country p = 0x" << this->mapController->pointToCountry(x, y) << std::endl;
}