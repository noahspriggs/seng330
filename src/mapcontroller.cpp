#include "mapcontroller.h"
#include "turncontroller.h"


MapController::MapController() {
    this->map = new Map();
}

void MapController::update()
{
    sf::Texture result;
    result.create(this->map->getWidth(), this->map->getHeight());
    
    sf::Uint8* pixels = new sf::Uint8[this->map->getWidth() * this->map->getHeight() * 4]; 
    
    // fill with white
    for(int y = 0; y < this->map->getHeight(); y++) 
    {
        for(int x = 0; x < this->map->getWidth(); x++) 
        {
            //draw highlighted countries
            if (turnController->playerList[0]->ownsCountry(pointToCountry(x,y))) {
                pixels[(y * this->map->getWidth() + x) * 4] = 0x00;
                pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x99;
                pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x77;
                pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
            } else if (turnController->playerList[1]->ownsCountry(pointToCountry(x,y))) {
                pixels[(y * this->map->getWidth() + x) * 4] = 0xBB;
                pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x33;
                pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x33;
                pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
            }
        }
    }
    
    // just draw the lines outlining the countries
    for(int x = 1; x < 3; x++) {
        for(int y = 0; y < this->map->getHeight(); y++) {
            pixels[(y * this->map->getWidth() + x * 300) * 4] = 0xFF;
            pixels[(y * this->map->getWidth() + x * 300) * 4 + 1] = 0x00;
            pixels[(y * this->map->getWidth() + x * 300) * 4 + 2] = 0xFF;
            pixels[(y * this->map->getWidth() + x * 300) * 4 + 3] = 0xFF;
        }
    }
    
    for(int y = 1; y < 3; y++) {
        for(int x = 0; x < this->map->getWidth(); x++) {
            pixels[(y * 300 * this->map->getWidth() + x) * 4] = 0xFF;
            pixels[(y * 300 * this->map->getWidth() + x) * 4 + 1] = 0x00;
            pixels[(y * 300 * this->map->getWidth() + x) * 4 + 2] = 0xFF;
            pixels[(y * 300 * this->map->getWidth() + x) * 4 + 3] = 0xFF;
        }
    }
    
    result.update(pixels);
    
    delete[] pixels;
    
    this->mapTexture = result;

}

sf::Texture MapController::getPixels()
{
    sf::Texture result;
    result.create(this->map->getWidth(), this->map->getHeight());
    
    sf::Uint8* pixels = new sf::Uint8[this->map->getWidth() * this->map->getHeight() * 4]; 
    
    // fill with white
    for(int y = 0; y < this->map->getHeight(); y++) 
    {
        for(int x = 0; x < this->map->getWidth(); x++) 
        {
            //draw highlighted countries
            if (turnController->playerList[0]->ownsCountry(pointToCountry(x,y))) {
                pixels[(y * this->map->getWidth() + x) * 4] = 0x00;
                pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x99;
                pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x77;
                pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
            } else if (turnController->playerList[1]->ownsCountry(pointToCountry(x,y))) {
                pixels[(y * this->map->getWidth() + x) * 4] = 0xBB;
                pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x33;
                pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x33;
                pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
            }
        }
    }
    
    // just draw the lines outlining the countries
    for(int x = 1; x < 3; x++) {
        for(int y = 0; y < this->map->getHeight(); y++) {
            pixels[(y * this->map->getWidth() + x * 300) * 4] = 0xFF;
            pixels[(y * this->map->getWidth() + x * 300) * 4 + 1] = 0x00;
            pixels[(y * this->map->getWidth() + x * 300) * 4 + 2] = 0xFF;
            pixels[(y * this->map->getWidth() + x * 300) * 4 + 3] = 0xFF;
        }
    }
    
    for(int y = 1; y < 3; y++) {
        for(int x = 0; x < this->map->getWidth(); x++) {
            pixels[(y * 300 * this->map->getWidth() + x) * 4] = 0xFF;
            pixels[(y * 300 * this->map->getWidth() + x) * 4 + 1] = 0x00;
            pixels[(y * 300 * this->map->getWidth() + x) * 4 + 2] = 0xFF;
            pixels[(y * 300 * this->map->getWidth() + x) * 4 + 3] = 0xFF;
        }
    }
    
    result.update(pixels);
    
    delete[] pixels;
    
    return result;
}

Country* MapController::pointToCountry(int x, int y)
{
    int continent = y / 300;
    int country = x / 300;
    
    return this->map->getContinents()[continent]->countries[country];
}

sf::Texture MapController::getMapTexture() {
    return this->mapTexture;
}
