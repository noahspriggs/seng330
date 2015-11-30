#include <iostream>
#include <cstdio>
#include <time.h>
#include <fstream>
#include <streambuf>
#include "mapcontroller.h"
#include "turncontroller.h"

//initializes the map
MapController::MapController() {
    this->map = new Map(time(NULL));
}

void MapController::update()
{
#ifndef RISKTEST
    this->mapTexture = getPixels();
#endif
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
			if (this->map->isPointSealane(x, y))
			{
				pixels[(y * this->map->getWidth() + x) * 4] = 0x87;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0xCE;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0xFA;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}
			else if (this->map->isPointShallow(x, y))
			{
				pixels[(y * this->map->getWidth() + x) * 4] = 0x3B;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x00;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0xCC;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}
			else if (!this->map->isPointOnLand(x, y))
			{
				pixels[(y * this->map->getWidth() + x) * 4] = 0x2B;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x00;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x94;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}
			else if (this->map->isPointBorder(x, y))
			{
				pixels[(y * this->map->getWidth() + x) * 4] = 0x00;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x00;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x00;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}
			else if(turnController->playerList[0]->ownsCountry(pointToCountry(x, y)))
			{
				pixels[(y * this->map->getWidth() + x) * 4] = playerColours[0].r;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = playerColours[0].g;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = playerColours[0].b;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}
			else if (turnController->playerList[1]->ownsCountry(pointToCountry(x, y)))
			{
                pixels[(y * this->map->getWidth() + x) * 4] = playerColours[1].r;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = playerColours[1].g;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = playerColours[1].b;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}
			else
			{
				pixels[(y * this->map->getWidth() + x) * 4] = 0x00;
				pixels[(y * this->map->getWidth() + x) * 4 + 1] = 0x94;
				pixels[(y * this->map->getWidth() + x) * 4 + 2] = 0x2B;
				pixels[(y * this->map->getWidth() + x) * 4 + 3] = 0xFF;
			}

        }
    }

    result.update(pixels);

    delete[] pixels;

    return result;
}
//points to another country which is positioned at the value which is calculated as following


Country* MapController::pointToCountry(int x, int y)
{
	return this->map->getCountryById(this->map->getCountryMap()[y * this->map->width + x]);
}

sf::Texture MapController::getMapTexture() {
    return this->mapTexture;
}

bool MapController::loadMap() {
    std::ifstream t("savedConfig.json");
    std::string mapStr((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    Json::Value root;
    Json::Reader reader;

    if(! reader.parse(mapStr,root)) {
        // std::cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
        std::cout <<"Loading new game\n";
        return false;
    }

	delete map;

	unsigned long long seed;
	sscanf(root["seed"].asString().c_str(), "%llx", &seed);

	map = new Map(seed);
	turnController->activePlayer = root["turn"].asInt();

	const Json::Value countryList = root["countries"];
	for (int i = 0; i < countryList.size(); i++)
	{
		const Json::Value country = countryList[i];

		if (country["owner"].asInt() > 0)
		{
			turnController->playerList[country["owner"].asInt() - 1]->addCountry(this->map->getCountryById(i));
		}
		this->map->getCountryById(i)->setUnits(country["units"].asInt());
	}

    return true;
}

void MapController::saveMap() {

	Json::Value root;

	std::stringstream ss;
	ss << std::hex << this->map->getSeed();
	root["seed"] = ss.str();

	for (int k = 0; k < turnController->playerList.size(); k++) {
		if (turnController->playerList[k] == turnController->getActivePlayer())
		{
			root["turn"] = k;
		}
	}

	Json::Value countryList;

	for (int i = 0; i < this->map->getNumCountries(); i++)
	{
		Json::Value country;
		for (int k = 0; k < turnController->playerList.size(); k++)
		{
			if (std::find(turnController->playerList[k]->countries.begin(), turnController->playerList[k]->countries.end(), this->map->getCountryById(i)) != turnController->playerList[k]->countries.end())
			{
				country["owner"] = k + 1;
				break;
			}
			else
			{
				country["owner"] = 0;
			}
		}

		country["units"] = this->map->getCountryById(i)->getUnits();
		countryList.append(country);
	}

	root["countries"] = countryList;

    Json::StyledWriter writer;

    std::ofstream myfile;
    myfile.open ("savedConfig.json");
    myfile << writer.write(root);

    myfile.close();
}
