#include "country.h"

Country::Country() 
{
    // for the purposes of the demo, each country is a 300x300 square with no other features
    this->width = this->height = 300;
    this->units = 0;
    
    this->mask = new int[this->width * this->height];
    for(int y = 0; y < this->height; y++)  {
        for(int x = 0; x < this->width; x++) {
            this->mask[y * this->width + x] = 1;
        }
    }
    highlight = false;
    
}

void Country::addNeighbour(Country* neighbour)
{
    this->neighbours.push_back(neighbour);
}

