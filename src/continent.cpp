#include "continent.h"

Continent::Continent() {

}

void Continent::addCountry(Country* country)
{
    this->countries.push_back(country);
}

