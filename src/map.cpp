#include "map.h"
#include "country.h"

Map::Map() {
    
    for(int y = 0; y < 3; y++) {
        Continent* rowContinent = new Continent();
        
        for(int x = 0; x < 3; x++) {
			Country* newCountry = new Country();
			newCountry->xPosition = x * 300;
			newCountry->yPosition = y * 300;

			rowContinent->addCountry(newCountry);
        }
        
        rowContinent->countries[0]->addNeighbour(rowContinent->countries[1]);
        rowContinent->countries[1]->addNeighbour(rowContinent->countries[0]);
        rowContinent->countries[1]->addNeighbour(rowContinent->countries[2]);
        rowContinent->countries[2]->addNeighbour(rowContinent->countries[1]);
        
        this->continents.push_back(rowContinent);
    }
    
    this->continents[0]->countries[0]->addNeighbour(this->continents[1]->countries[0]);
    this->continents[0]->countries[1]->addNeighbour(this->continents[1]->countries[1]);
    this->continents[0]->countries[2]->addNeighbour(this->continents[1]->countries[2]);
    
    this->continents[1]->countries[0]->addNeighbour(this->continents[0]->countries[0]);
    this->continents[1]->countries[1]->addNeighbour(this->continents[0]->countries[1]);
    this->continents[1]->countries[2]->addNeighbour(this->continents[0]->countries[2]);
    this->continents[1]->countries[0]->addNeighbour(this->continents[2]->countries[0]);
    this->continents[1]->countries[1]->addNeighbour(this->continents[2]->countries[1]);
    this->continents[1]->countries[2]->addNeighbour(this->continents[2]->countries[2]);
    
    this->continents[2]->countries[0]->addNeighbour(this->continents[1]->countries[0]);
    this->continents[2]->countries[1]->addNeighbour(this->continents[1]->countries[1]);
    this->continents[2]->countries[2]->addNeighbour(this->continents[1]->countries[2]);
    
    this->width = this->height = 900;
    
}

std::vector<Continent*> Map::getContinents()
{
    return this->continents;
}

int Map::getWidth()
{
    return this->width;
}
 
int Map::getHeight()
{
    return this->height;
}
