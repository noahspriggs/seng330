#include "map.h"
#include "country.h"

Map::Map() {

	int* mask = new int[300 * 300];
	for (int y = 0; y < 300; y++) {
		for (int x = 0; x < 300; x++) {
			mask[y * 300 + x] = 1;
		}
	}

	//for the new continent on the board
    for(int y = 0; y < 3; y++) {
        Continent* rowContinent = new Continent();

        for(int x = 0; x < 3; x++) {
			rowContinent->addCountry(new Country(300, 300, mask, x * 300, y * 300, 130, 130));
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
