#include <iostream>
#include <cstdio>

#include <fstream>
#include <streambuf>
#include "mapcontroller.h"
#include "turncontroller.h"


MapController::MapController() {
    this->map = new Map();
}

void MapController::update()
{
#ifndef RISKTEST
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

bool MapController::loadMap() {
    std::vector<Country*> countryIndex;
    std::ifstream t("savedConfig.json");
    std::string mapStr((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    Json::Value root;
    Json::Reader reader;
    Map* map = new Map();

    // std::cout << "MAP STRING:\n";
    // std::cout << mapStr;
    if(! reader.parse(mapStr,root)) {
        std::cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
        return false;
    }

    const Json::Value mapValue = root["map"];

    //map has int height/width and continent vector

    map->height = mapValue["height"].asInt();
    map->width = mapValue["width"].asInt();

    const Json::Value continentListValue = mapValue["continents"];
    std::vector<Continent*> continents;
    for(int i = 0; i < continentListValue.size(); i++) {

        const Json::Value countryListValue = continentListValue[i]["countries"];
        std::vector<Country*> countries;
        Continent* cont = new Continent();
        for(int j = 0; j < countryListValue.size(); j++) {
            Country* country = new Country();
            country->height = countryListValue[j]["height"].asInt();
            country->width = countryListValue[j]["width"].asInt();
            country->units = countryListValue[j]["units"].asInt();

            country->xPosition = countryListValue[j]["xPosition"].asInt();
            country->yPosition = countryListValue[j]["yPosition"].asInt();
            country->centerOffsetX = countryListValue[j]["centerOffsetX"].asInt();
            country->centerOffsetY = countryListValue[j]["centerOffsetY"].asInt();

            // int* mask = new int[countryListValue[j]["mask"].size()];
            // for(int k = 0; k < mask.size(); k++) {
                // mask[k] = countryListValue[j]["mask"][k].asInt();
            // }
            // country->mask = mask;
            int owner = countryListValue[j]["ownedBy"].asInt();
            std::cout << owner << std::endl;
            if(owner > 0) {
                turnController->playerList[owner-1]->countries.push_back(country);
            }
            countries.push_back(country);
            countryIndex.push_back(country);
            /*int width;
            int height;
            int* mask;
            int units;

            int xPosition;
            int yPosition;

            int centerOffsetX;
            int centerOffsetY;

            std::vector<Country*> neighbours;*/
        }

        cont->countries = countries;
        continents.push_back(cont);

    }

    for(int i = 0; i < continentListValue.size(); i++) {

        const Json::Value countryListValue = continentListValue[i]["countries"];

        for(int j = 0; j < countryListValue.size(); j++) {

            for(int k = 0; k < countryListValue[j]["neighbours"].size(); k++){

                continents[i]->countries[j]->neighbours.push_back(countryIndex[countryListValue[j]["neighbours"][k].asInt()]);
            }
        }
    }

    map->continents = continents;

    for(int i = 0; i<map->continents.size();i++) {
        for(int j = 0; j<map->continents[i]->countries.size();j++) {
            Country* cur = map->continents[i]->countries[j];
            std::cout << cur->units;
        }
        std::cout << std::endl;
    }
    for(int i = 0; i<turnController->playerList.size();i++) {
        std::cout << "player " << i << std::endl;
        for(int j = 0; j<turnController->playerList[i]->countries.size();j++) {
            Country* cur = turnController->playerList[i]->countries[j];
            std::cout << cur->units;
        }

    }



    return true;

}

void MapController::saveMap() {

    Json::Value root;
    Json::Value mapValue;
    mapValue["height"] = map->height;
    mapValue["width"] = map->width;

    std::vector<Country*> countries;
    for(int i = 0; i < map->continents.size(); i++) {
        for(int j = 0; j<map->continents[i]->countries.size();j++) {
            countries.push_back(map->continents[i]->countries[j]);
            }
    }

    for(int i = 0; i < map->continents.size(); i++) {
        Json::Value continentListValue;

        Json::Value countryListValue;
        for(int j = 0; j<map->continents[i]->countries.size();j++) {
            Country* cur = map->continents[i]->countries[j];
            Json::Value country;
            Json::Value neighbours;
            Json::Value mask;
            country["width"] = cur->getWidth();
            country["height"] = cur->getHeight();
            country["units"] = cur->getUnits();
            country["xPosition"] = cur->getXPosition();
            country["yPosition"] = cur->getYPosition();
            country["centerOffsetX"] = cur->getCenterOffsetX();
            country["centerOffsetY"] = cur->getCenterOffsetY();
            // for(int k = 0;k<cur->mask.size();k++) {
                // mask.append(cur->mask[k]);
            // }
            for(int k = 0;k<cur->neighbours.size();k++) {
                for(int l = 0; l<countries.size();l++) {
                    if(cur->getNeighbours()[k] == countries[l]) {
                        neighbours.append(l);
                    }
                }
            }
            country["mask"] = mask;
            country["neighbours"] = neighbours;
            for(int k = 0;k<turnController->playerList.size();k++) {
                if(std::find(turnController->playerList[k]->countries.begin(),turnController->playerList[k]->countries.end(),cur) != turnController->playerList[k]->countries.end()) {
                    country["ownedBy"] = k+1;
                    break;
                } else {
                    country["ownedBy"] = 0;

                }
            }

            countryListValue.append(country);
        }

        continentListValue["countries"] = countryListValue;
        mapValue["continents"].append(continentListValue);

    }
    root["map"] = mapValue;

    Json::StyledWriter writer;
    std::cout << writer.write(root);

    std::ofstream myfile;
    myfile.open ("savedConfig.json");
    myfile << writer.write(root);

    myfile.close();
}
