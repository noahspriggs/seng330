#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>

#include "map.h"
#include "country.h"
#include "opensimplexnoise.h"

// internal class for the priority queue comparator
class EuclideanComparator
{
	int tX, tY;
public:
	EuclideanComparator(int x, int y)
	{
		tX = x;
		tY = y;
	}

	bool operator() (const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const
	{
		return (lhs.first - tX) * (lhs.first - tX) + (lhs.second - tY) * (lhs.second - tY) <
			(rhs.first - tX) * (rhs.first - tX) + (rhs.second - tY) * (rhs.second - tY);
	}
};


static const int numCountries = 21;
const double waterLevel = 0.5;
const double shallowWaterLevel = 0.465;

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
	// currently done by flood fill
	countryMap = new int[width * height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			countryMap[x * width + y] = -1;
		}
	}

	std::vector<int> xFloodFill[numCountries];
	std::vector<int> yFloodFill[numCountries];

	for (int i = 0; i < numCountries; i++)
	{
		xFloodFill[i].push_back(centerX[i]);
		yFloodFill[i].push_back(centerY[i]);
	}

	bool filledSomething = false;

	do
	{
		filledSomething = false;

		for (int i = 0; i < numCountries; i++)
		{
			std::vector<int> nextGenX;
			std::vector<int> nextGenY;

			for (int j = 0; j < xFloodFill[i].size(); j++)
			{
				int cX = xFloodFill[i][j];
				int cY = yFloodFill[i][j];
			
				if (countryMap[cY * width + cX] == -1)
				{
					countryMap[cY * width + cX] = i;
					filledSomething = true;

					if (cX - 1 >= 0 && countryMap[cY * width + cX - 1] == -1 && isPointOnLand(cX - 1, cY))
					{
						nextGenX.push_back(cX - 1);
						nextGenY.push_back(cY);
					}
					if (cX + 1 < width && countryMap[cY * width + cX + 1] == -1 && isPointOnLand(cX + 1, cY))
					{
						nextGenX.push_back(cX + 1);
						nextGenY.push_back(cY);
					}
					if (cY - 1 >= 0 && countryMap[(cY - 1) * width + cX] == -1 && isPointOnLand(cX, cY - 1))
					{
						nextGenX.push_back(cX);
						nextGenY.push_back(cY - 1);
					}
					if (cY + 1 < height && countryMap[(cY + 1) * width + cX] == -1 && isPointOnLand(cX, cY + 1))
					{
						nextGenX.push_back(cX);
						nextGenY.push_back(cY + 1);
					}
				}
			}

			std::swap(xFloodFill[i], nextGenX);
			std::swap(yFloodFill[i], nextGenY);

			//if (cX - 1 >= 0 && cY - 1 >= 0 && countryMap[(cY - 1) * width + cX - 1] == -1 && isPointOnLand(cX - 1, cY - 1))
			//{
			//	xFloodFill[i].push(cX - 1);
			//	yFloodFill[i].push(cY - 1);
			//}
			//if (cX + 1 < width && cY - 1 >= 0 && countryMap[(cY - 1) * width + cX + 1] == -1 && isPointOnLand(cX + 1, cY - 1))
			//{
			//	xFloodFill[i].push(cX + 1);
			//	yFloodFill[i].push(cY - 1);
			//}
			//if (cX - 1 >= 0 && cY + 1 < height && countryMap[(cY + 1) * width + cX - 1] == -1 && isPointOnLand(cX - 1, cY + 1))
			//{
			//	xFloodFill[i].push(cX - 1);
			//	yFloodFill[i].push(cY + 1);
			//}
			//if (cX + 1 < width && cY + 1 < height && countryMap[(cY + 1) * width + cX + 1] == -1 && isPointOnLand(cX + 1, cY + 1))
			//{
			//	xFloodFill[i].push(cX + 1);
			//	yFloodFill[i].push(cY + 1);
			//}
		}
	} 
	while (filledSomething);

	for (int i = 0; i < numCountries; i++)
	{
		std::vector<int> empty1;
		std::vector<int> empty2;

		std::swap(xFloodFill[i], empty1);
		std::swap(yFloodFill[i], empty2);
	}

	//for (int x = 0; x < width; x++)
	//{
	//	for (int y = 0; y < height; y++)
	//	{
	//		countryMap[y * width + x] = -1;

	//		if (isPointOnLand(x, y))
	//		{
	//			// first find what country this point is in
	//			int currentCountry = 0;
	//			double distanceSquaredToCurrentCountry = (width * width + height * height) + 1.0;
	//			for (int i = 0; i < numCountries; i++)
	//			{
	//				double dX = centerX[i] - x;
	//				double dY = centerY[i] - y;
	//				double euclideanDistanceSquared = dX * dX + dY * dY;

	//				if (euclideanDistanceSquared < distanceSquaredToCurrentCountry)
	//				{
	//					currentCountry = i;
	//					distanceSquaredToCurrentCountry = euclideanDistanceSquared;
	//				}
	//			}

	//			countryMap[y * width + x] = currentCountry;
	//		}
	//	}
	//}

	isBorder = new bool[width * height];

	// then check us against those above, to the left, and to the above-left
	// of us for being different countries
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int currentCountry = countryMap[y * width + x];

			if (isPointOnLand(x, y) && currentCountry != -1)
			{
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
	int numContinents = 0;

	for (int i = 0; i < numCountries; i++)
	{
		continentMap[countries[i]] = -1;
	}

	for (int i = 0; i < numCountries; i++)
	{
		if (continentMap[countries[i]] == -1)
		{
			std::queue<Country*> bfsQueue;
			bfsQueue.push(countries[i]);
			continentMap[countries[i]] = numContinents;

			while (!bfsQueue.empty())
			{
				Country* currentCountry = bfsQueue.front();
				bfsQueue.pop();
				
				std::vector<Country*> neighbours = currentCountry->getNeighbours();
				for (int j = 0; j < neighbours.size(); j++)
				{
					if (continentMap[neighbours[j]] == -1)
					{
						continentMap[neighbours[j]] = numContinents;
						bfsQueue.push(neighbours[j]);
					}
				}
			}

			numContinents++;
		}
	}

	// and then create continent objects 
	for (int i = 0; i < numContinents; i++)
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

	// number the oceans
	int* oceans = new int[width * height];
	int numOceans = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			oceans[y * width + x] = -1;
		}
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (!isPointOnLand(x, y) && oceans[y * width + x] == -1)
			{
				// flood fill this ocean

				std::vector<int> xFill;
				std::vector<int> yFill;
				bool filledSomethingOcean = false;

				xFill.push_back(x);
				yFill.push_back(y);

				do
				{
					filledSomethingOcean = false;

					std::vector<int> nextX;
					std::vector<int> nextY;

					for (int j = 0; j < xFill.size(); j++)
					{
						int cX = xFill[j];
						int cY = yFill[j];

						if (oceans[cY * width + cX] == -1)
						{
							oceans[cY * width + cX] = numOceans;
							filledSomethingOcean = true;

							if (cX - 1 >= 0 && !isPointOnLand(cX - 1, cY))
							{
								nextX.push_back(cX - 1);
								nextY.push_back(cY);
							}
							if (cX + 1 < width && !isPointOnLand(cX + 1, cY))
							{
								nextX.push_back(cX + 1);
								nextY.push_back(cY);
							}
							if (cY - 1 >= 0 && !isPointOnLand(cX, cY - 1))
							{
								nextX.push_back(cX);
								nextY.push_back(cY - 1);
							}
							if (cY + 1 < height && !isPointOnLand(cX, cY + 1))
							{
								nextX.push_back(cX);
								nextY.push_back(cY + 1);
							}
						}
					}

					std::swap(xFill, nextX);
					std::swap(yFill, nextY);
				} while (filledSomethingOcean);

				numOceans++;
			}
		}
	}

	// now mark the countires adjacent to each ocean
	std::vector<int>* oceanNeighbours = new std::vector<int>[numOceans];
	std::vector<int>** xCoastlines = new std::vector<int>*[numCountries];
	std::vector<int>** yCoastlines = new std::vector<int>*[numCountries];

	for (int i = 0; i < numCountries; i++)
	{
		xCoastlines[i] = new std::vector<int>[numOceans];
		yCoastlines[i] = new std::vector<int>[numOceans];
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int currentCountry = countryMap[y * width + x];

			if (isPointOnLand(x, y) && currentCountry != -1)
			{
				if (y > 0)
				{
					int above = oceans[(y - 1) * width + x];
					if (above != -1)
					{
						xCoastlines[currentCountry][above].push_back(x);
						yCoastlines[currentCountry][above].push_back(y - 1);

						if (std::find(oceanNeighbours[above].begin(), oceanNeighbours[above].end(), currentCountry) == oceanNeighbours[above].end())
						{
							oceanNeighbours[above].push_back(currentCountry);
						}
					}
				}

				if (x > 0)
				{
					int left = oceans[y * width + x - 1];
					if (left != -1)
					{
						xCoastlines[currentCountry][left].push_back(x - 1);
						yCoastlines[currentCountry][left].push_back(y);

						if (std::find(oceanNeighbours[left].begin(), oceanNeighbours[left].end(), currentCountry) == oceanNeighbours[left].end())
						{
							oceanNeighbours[left].push_back(currentCountry);
						}
					}
				}

				if (y < height - 1)
				{
					int below = oceans[(y + 1) * width + x];
					if (below != -1)
					{
						xCoastlines[currentCountry][below].push_back(x);
						yCoastlines[currentCountry][below].push_back(y + 1);

						if (std::find(oceanNeighbours[below].begin(), oceanNeighbours[below].end(), currentCountry) == oceanNeighbours[below].end())
						{
							oceanNeighbours[below].push_back(currentCountry);
						}
					}
				}

				if (x < width - 1)
				{
					int right = oceans[y * width + x + 1];
					if (right != -1)
					{
						xCoastlines[currentCountry][right].push_back(x + 1);
						yCoastlines[currentCountry][right].push_back(y);

						if (std::find(oceanNeighbours[right].begin(), oceanNeighbours[right].end(), currentCountry) == oceanNeighbours[right].end())
						{
							oceanNeighbours[right].push_back(currentCountry);
						}
					}
				}
			}
		}
	}

	// get the continents adjacent to each ocean
	std::vector<int>* oceanContinents = new std::vector<int>[numOceans];
	std::vector<int>** countryContinentOceanNeighbours = new std::vector<int>*[numOceans];

	for (int i = 0; i < numOceans; i++)
	{
		countryContinentOceanNeighbours[i] = new std::vector<int>[this->continents.size()];
	}

	for (int i = 0; i < this->continents.size(); i++)
	{
		for (int j = 0; j < numOceans; j++)
		{
			for (int k = 0; k < oceanNeighbours[j].size(); k++)
			{
				Country* currentCountry = countries[oceanNeighbours[j][k]];
				if (std::find(this->continents[i]->countries.begin(), this->continents[i]->countries.end(), currentCountry) != this->continents[i]->countries.end())
				{
					countryContinentOceanNeighbours[j][i].push_back(oceanNeighbours[j][k]);

					if (std::find(oceanContinents[j].begin(), oceanContinents[j].end(), i) == oceanContinents[j].end())
					{
						oceanContinents[j].push_back(i);
					}
				}
			}
		}
	}

	isSealane = new bool[width * height];
	std::vector<int> linesStartX;
	std::vector<int> linesStartY;
	std::vector<int> linesEndX;
	std::vector<int> linesEndY;

	for (int i = 0; i < numOceans; i++)
	{
		// add sealanes if the ocean has 2 or more countries
		for (int j = 0; j < oceanContinents[i].size() && oceanContinents[i].size() >= 2; j++)
		{
			int startContinent = oceanContinents[i][j];
			int endContinent = oceanContinents[i][(j + 1) % oceanContinents[i].size()];

			// pick a random start and end for the sealane
			int startCountry = rand() % countryContinentOceanNeighbours[i][startContinent].size();
			int endCountry = rand() % countryContinentOceanNeighbours[i][endContinent].size();

			startCountry = countryContinentOceanNeighbours[i][startContinent][startCountry];
			endCountry = countryContinentOceanNeighbours[i][endContinent][endCountry];

			// pick random points on their coastlines
			int coastlineStartPoint = rand() % xCoastlines[startCountry][i].size();
			int coastlineEndPoint = rand() % xCoastlines[endCountry][i].size();

			int startX = xCoastlines[startCountry][i][coastlineStartPoint];
			int startY = yCoastlines[startCountry][i][coastlineStartPoint];

			int endX = xCoastlines[endCountry][i][coastlineEndPoint];
			int endY = yCoastlines[endCountry][i][coastlineEndPoint];

			// first go through the lines, and mark the points where they go on and off land

			double length = sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));

			double dX = (double)(endX - startX) / length;
			double dY = (double)(endY - startY) / length;

			double cX = startX;
			double cY = startY;
			int iCX = lround(cX);
			int iCY = lround(cY);

			for (int q = 0; q <= (int)ceil(length); q++)
			{
				if (isPointOnLand(iCX, iCY) && countryMap[iCY * width + iCX] != -1)
				{
					int otherCountry = countryMap[iCY * width + iCX];

					if (otherCountry == startCountry)
					{
						startX = iCX;
						startY = iCY;
					}
					else if (otherCountry == endCountry)
					{
						endX = iCX;
						endY = iCY;
						break;
					}
					else if (continentMap[countries[otherCountry]] == continentMap[countries[startCountry]])
					{
						startCountry = otherCountry;
						startX = iCX;
						startY = iCY;
					}
					else if (continentMap[countries[otherCountry]] == continentMap[countries[endCountry]])
					{
						endCountry = otherCountry;
						endX = iCX;
						endY = iCY;
						break;
					}
					else
					{
						linesStartX.push_back(startX);
						linesStartY.push_back(startY);
						linesEndX.push_back(iCX);
						linesEndY.push_back(iCY);

						countries[startCountry]->addNeighbour(countries[otherCountry]);
						countries[otherCountry]->addNeighbour(countries[startCountry]);

						startCountry = otherCountry;
						startX = iCX;
						startY = iCY;
					}
				}

				cX += dX;
				cY += dY;
				iCX = lround(cX);
				iCY = lround(cY);
			}

			linesStartX.push_back(startX);
			linesStartY.push_back(startY);
			linesEndX.push_back(endX);
			linesEndY.push_back(endY);

			countries[startCountry]->addNeighbour(countries[endCountry]);
			countries[endCountry]->addNeighbour(countries[startCountry]);
		}
	}

	// draw the sealanes
	for (int i = 0; i < linesStartX.size(); i++)
	{
		int startX = linesStartX[i];
		int startY = linesStartY[i];
		int endX = linesEndX[i];
		int endY = linesEndY[i];

		double length = sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));

		double dX = (double)(endX - startX) / length;
		double dY = (double)(endY - startY) / length;

		double cX = startX;
		double cY = startY;
		int iCX = lround(cX);
		int iCY = lround(cY);

		for (int q = 0; q <= (int)ceil(length); q++)
		{
			isSealane[iCY * width + iCX] = true;

			cX += dX;
			cY += dY;
			iCX = lround(cX);
			iCY = lround(cY);
		}
	}

	delete[] oceans;

	delete[] oceanNeighbours;

	for (int i = 0; i < numCountries; i++)
	{
		delete[] xCoastlines[i];
		delete[] yCoastlines[i];
	}


	delete[] xCoastlines;
	delete[] yCoastlines;

	delete[] oceanContinents;

	for (int i = 0; i < numOceans; i++)
	{
		delete[] countryContinentOceanNeighbours[i];
	}

	delete[] countryContinentOceanNeighbours;

	// find all countries bordering the oceans


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
	if (isSealane != NULL)
	{
		delete[] isSealane;
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

bool Map::isPointSealane(int x, int y)
{
	return isSealane[y * width + x];
}

bool Map::isPointShallow(int x, int y)
{
	return (this->currentFbm != NULL && this->currentFbm[y * width + x] <= waterLevel && this->currentFbm[y * width + x] > shallowWaterLevel);
}