#include <stdlib.h>
#include <math.h>
#include <stack>
#include <map>
#include <algorithm>
#include <iostream>

#include "map.h"
#include "country.h"
#include "opensimplexnoise.h"


static const int numCountries = 21;

Map::Map(unsigned long long seed) {
	const double minCountrySeparation = 50;
	const int minDistanceFromEdge = 50;

	this->width = this->height = 900;
	this->seed = seed;
	srand(0x00000000FFFFFFFF & seed);

	// first place the countries randomly, ensuring no two countries are
	// less than minCountrySeparation units from eachother, and both are on land
	// using the FBM
	double* fbm = getFBM();

	int centerX[numCountries];
	int centerY[numCountries];

	int numPointsLocated = 0;
	while (numPointsLocated < numCountries)
	{
		centerX[numPointsLocated] = rand() % (width - minDistanceFromEdge * 2) + minDistanceFromEdge;
		centerY[numPointsLocated] = rand() % (height - minDistanceFromEdge * 2) + minDistanceFromEdge;

		if (!isPointOnLand(centerX[numPointsLocated], centerY[numPointsLocated])) 
		{
			continue;
		}

		bool newPointValid = true;
		for (int i = 0; i < numPointsLocated; i++)
		{
			double dX = centerX[i] - centerX[numPointsLocated];
			double dY = centerY[i] - centerY[numPointsLocated];
			double euclideanDistance = sqrt(dX * dX + dY * dY);

			if (euclideanDistance < minCountrySeparation)
			{
				newPointValid = false;
				break;
			}
		}

		if (newPointValid)
		{
			numPointsLocated++;
		}
	}
	
	// acutally create the country objects
	countries = new Country*[numCountries];

	int* mask = new int[300 * 300];
	for (int y = 0; y < 300; y++) {
		for (int x = 0; x < 300; x++) {
			mask[y * 300 + x] = 1;
		}
	}

	for (int i = 0; i < numCountries; i++)
	{
		countries[i] = new Country(centerX[i], centerY[i]);
	}


	// now use the fbm to
	// find neighbouring countries
	// currently done by a (disgusting) pixel-by-pixel check
	countryMap = new int[width * height];
	isBorder = new bool[width * height];

	for (int x = 0; x < width; x++) 
	{
		for (int y = 0; y < height; y++) 
		{
			countryMap[y * width + x] = -1;

			if (isPointOnLand(x, y))
			{
				// first find what country this point is in
				int currentCountry = 0;
				double distanceSquaredToCurrentCountry = (width * width + height * height) + 1.0;
				for (int i = 0; i < numCountries; i++)
				{
					double dX = centerX[i] - x;
					double dY = centerY[i] - y;
					double euclideanDistanceSquared = dX * dX + dY * dY;

					if (euclideanDistanceSquared < distanceSquaredToCurrentCountry)
					{
						currentCountry = i;
						distanceSquaredToCurrentCountry = euclideanDistanceSquared;
					}
				}

				countryMap[y * width + x] = currentCountry;

				// then check us against those above, to the left, and to the above-left
				// of us for being different countries

				if (y > 0)
				{
					int above = countryMap[(y - 1) * width + x];
					if (above != -1 && above != currentCountry)
					{
						isBorder[above] = true;
						isBorder[y * width + x] = true;

						// we are beside a different country, is it not already added?
						std::vector<Country*> currentCountryNeighbours = countries[currentCountry]->getNeighbours();
						if (std::find(currentCountryNeighbours.begin(), currentCountryNeighbours.end(), countries[above]) == currentCountryNeighbours.end())
						{
							// it's not already a neighbour, add it
							countries[above]->addNeighbour(countries[currentCountry]);
							countries[currentCountry]->addNeighbour(countries[above]);
						}
					}
				}

				if (x > 0)
				{
					int left = countryMap[y * width + x - 1];
					if (left != -1 && left != currentCountry)
					{
						isBorder[left] = true;
						isBorder[y * width + x] = true;

						// we are beside a different country, is it not already added?
						std::vector<Country*> currentCountryNeighbours = countries[currentCountry]->getNeighbours();
						if (std::find(currentCountryNeighbours.begin(), currentCountryNeighbours.end(), countries[left]) == currentCountryNeighbours.end())
						{
							// it's not already a neighbour, add it
							countries[left]->addNeighbour(countries[currentCountry]);
							countries[currentCountry]->addNeighbour(countries[left]);
						}
					}
				}

				if (y > 0 && x > 0)
				{
					int aboveLeft = countryMap[(y - 1) * width + x - 1];
					if (aboveLeft != -1 && aboveLeft != currentCountry)
					{
						isBorder[aboveLeft] = true;
						isBorder[y * width + x] = true;

						// we are beside a different country, is it not already added?
						std::vector<Country*> currentCountryNeighbours = countries[currentCountry]->getNeighbours();
						if (std::find(currentCountryNeighbours.begin(), currentCountryNeighbours.end(), countries[aboveLeft]) == currentCountryNeighbours.end())
						{
							// it's not already a neighbour, add it
							countries[aboveLeft]->addNeighbour(countries[currentCountry]);
							countries[currentCountry]->addNeighbour(countries[aboveLeft]);
						}
					}
				}
			}
		}
	}

	// now sort the countries into continents
	std::map<Country*, int> continentMap;
	for (int i = 0; i < numCountries; i++)
	{
		continentMap[countries[i]] = i;
	}

	for (int i = 0; i < numCountries; i++)
	{
		Country* currentCountry = countries[i];
		std::vector<Country*> neighbours = currentCountry->getNeighbours();

		for (int i = 0; i < neighbours.size(); i++)
		{
			continentMap[neighbours[i]] = continentMap[currentCountry];
		}
	}

	// now count how many countries are in each continent
	int continentCount[numCountries];

	for (int i = 0; i < numCountries; i++)
	{
		continentCount[i] = 0;
	}

	for (int i = 0; i < numCountries; i++)
	{
		continentCount[continentMap[countries[i]]]++;
	}

	// and then create continent objects for those with more than one
	for (int i = 0; i < numCountries; i++)
	{
		if (continentCount[i] > 0)
		{
			Continent* cont = new Continent();

			for (int j = 0; j < numCountries; j++)
			{
				if (continentMap[countries[j]] == i)
				{
					cont->addCountry(countries[j]);
				}
			}

			this->continents.push_back(cont);
		}
	}

	///*!<initializing and adding new continent and country to the map respectively by using the for loop>*/
 //   for(int y = 0; y < 3; y++) {
 //       Continent* rowContinent = new Continent();

 //       for(int x = 0; x < 3; x++) {
	//		rowContinent->addCountry(new Country(300, 300, mask, x * 300, y * 300, 130, 130));
 //       }

 //       rowContinent->countries[0]->addNeighbour(rowContinent->countries[1]);
 //       rowContinent->countries[1]->addNeighbour(rowContinent->countries[0]);
 //       rowContinent->countries[1]->addNeighbour(rowContinent->countries[2]);
 //       rowContinent->countries[2]->addNeighbour(rowContinent->countries[1]);

 //       this->continents.push_back(rowContinent);
 //   }

 //   this->continents[0]->countries[0]->addNeighbour(this->continents[1]->countries[0]);
 //   this->continents[0]->countries[1]->addNeighbour(this->continents[1]->countries[1]);
 //   this->continents[0]->countries[2]->addNeighbour(this->continents[1]->countries[2]);

 //   this->continents[1]->countries[0]->addNeighbour(this->continents[0]->countries[0]);
 //   this->continents[1]->countries[1]->addNeighbour(this->continents[0]->countries[1]);
 //   this->continents[1]->countries[2]->addNeighbour(this->continents[0]->countries[2]);
 //   this->continents[1]->countries[0]->addNeighbour(this->continents[2]->countries[0]);
 //   this->continents[1]->countries[1]->addNeighbour(this->continents[2]->countries[1]);
 //   this->continents[1]->countries[2]->addNeighbour(this->continents[2]->countries[2]);

 //   this->continents[2]->countries[0]->addNeighbour(this->continents[1]->countries[0]);
 //   this->continents[2]->countries[1]->addNeighbour(this->continents[1]->countries[1]);
 //   this->continents[2]->countries[2]->addNeighbour(this->continents[1]->countries[2]);

}

Map::~Map()
{
	if (countries != NULL)
	{
		delete[] countries;
	}
	if (currentFbm != NULL)
	{
		delete[] currentFbm;
	}
	if (countryMap != NULL)
	{
		delete[] countryMap;
	}
	if (isBorder != NULL)
	{
		delete[] isBorder;
	}
}

std::vector<Continent*> Map::getContinents() /*!<a vector storing the continents and getting them from the map>*/
{
    return this->continents;
}

int Map::getWidth() // width of the map
{
    return this->width;
}

int Map::getHeight() // height of the map
{
    return this->height;
}

bool Map::isPointOnLand(int x, int y)
{
	const double waterLevel = 0.5;
	return (this->currentFbm != NULL && this->currentFbm[y * width + x] > waterLevel);
}

unsigned long long Map::getSeed()
{
	return seed;
}

double* Map::getFBM()
{
	const int ocataves = 10;
	const double lacunarity = 2.0;
	const double gain = 0.5;

	if (currentFbm != NULL)
	{
		return currentFbm;
	}

	currentFbm = new double[width * height];
	osn_context* noiseContext;
	open_simplex_noise(this->seed, &noiseContext);

	for (int x = 0; x < width; x++) 
	{
		for (int y = 0; y < height; y++) 
		{
			double total = 0.0;
			double frequency = 4.0 / width;
			double amplitude = gain;

			for (int j = 0; j < ocataves; j++) 
			{
				total += open_simplex_noise2(noiseContext, x * frequency, y * frequency) * amplitude;
				frequency *= lacunarity;
				amplitude *= gain;
			}

			currentFbm[y * width + x] = (total + 1.0) / 2.0;
		}
	}

	open_simplex_noise_free(noiseContext);
	return currentFbm;
}

int* Map::getCountryMap()
{
	return countryMap;
}

Country* Map::getCountryById(int id)
{
	if (countries != NULL && id >= 0)
	{
		return countries[id];
	}

	return NULL;
}

bool Map::isPointBorder(int x, int y)
{
	return isBorder[y * width + x];
}

int Map::getNumCountries()
{
	return numCountries;
}