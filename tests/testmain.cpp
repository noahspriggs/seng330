#include "gtest/gtest.h"
#include "mapcontroller.h"
#include "turncontroller.h"

// Tests if the map returns the correct country from pointtocountry for the
// default grid map
TEST(MapControllerTest, PointToCountryGivesCountryOrWater) 
{
	//MapController mapController;
	//Country* country = mapController.pointToCountry(400, 400);

	//if (mapController.map->isPointOnLand(400, 400))
	//{
	//	EXPECT_NE(country, (Country*)0);
	//}
	//else
	//{
	//	EXPECT_EQ(country, (Country*)0);
	//}
}

// Tests that the same player does not act immediatly after the end of 
// their own turn, instead waiting for the other player to act first
TEST(TurnControllerTest, PlayerDoesNotActTwiceInARow) 
{
	MapController mapController;
	TurnController turnController(&mapController);
	turnController.startGame();

	Player* player1 = turnController.getActivePlayer();
	turnController.endTurn();
	Player* player2 = turnController.getActivePlayer();

	EXPECT_NE(player1, player2);
}

// Tests that the players take turns one after the other
TEST(TurnControllerTest, PlayersActEveryOtherTurn) 
{
	MapController mapController;
	TurnController turnController(&mapController);
	turnController.startGame();

	Player* player1 = turnController.getActivePlayer();
	turnController.endTurn();
	turnController.endTurn();
	Player* player1again = turnController.getActivePlayer();

	EXPECT_EQ(player1, player1again);

	turnController.endTurn();
	Player* player2 = turnController.getActivePlayer();
	turnController.endTurn();
	turnController.endTurn();
	Player* player2again = turnController.getActivePlayer();

	EXPECT_EQ(player2, player2again);
}

// Tests that the players start the game with at least one country
TEST(PlayerTest, PlayersHaveAtLeastOneStartingCountry) 
{
	MapController mapController;
	TurnController turnController(&mapController);
	turnController.startGame();
	Player* player1 = turnController.getActivePlayer();
	turnController.endTurn();
	Player* player2 = turnController.getActivePlayer();

	int numCoutries1 = 0;
	int numCoutries2 = 0;
	for (int i = 0; i < mapController.map->getContinents().size(); i++)
	{
		for (int j = 0; j < mapController.map->getContinents()[i]->countries.size(); j++)
		{
			if (player1->ownsCountry(mapController.map->getContinents()[i]->countries[j]))
			{
				numCoutries1++;
			}
			if (player2->ownsCountry(mapController.map->getContinents()[i]->countries[j]))
			{
				numCoutries2++;
			}
		}
	}

	EXPECT_GE(numCoutries1, 1);
	EXPECT_GE(numCoutries2, 1);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}