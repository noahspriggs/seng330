#include "continent.h"

Continent::Continent() {

}

void Continent::addCountry(Country* country)
{
	/*pushes the country*/
    this->countries.push_back(country);
}

