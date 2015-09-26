
//	--	Include Statements	--

#include <time.h>

#include "GameMap.h"

//	--	End Include Statements	--

//	-- Define Statements	--

#define NUM_TERRAIN 7

//	--	End Define Statements	--

using namespace std;

GameMap::GameMap(void)
{
}


GameMap::~GameMap(void)
{
}


vector< vector<GamePiece*> >GameMap::ConstructMap(int mapWidth, int mapHeight)
{
	vector< vector<GamePiece*> > map;
	map.resize(mapWidth);

	for (int i = 0; i < mapWidth; ++i)
		map[i].resize(mapHeight);
	
	//	--	Setup terrain	--

	Terrain* terrainTypes [NUM_TERRAIN * 3];							// Times 3 to account for holy/blighted variants
	terrainTypes[0] = new Terrain("Plain", 0, 1, 0, 0.0f, 0.0f, 0);		// Plains
	terrainTypes[1] = new Terrain("Badland", 1, 2, 0, 0.0f, 0.0f, 0);		// Badlands
	terrainTypes[2] = new Terrain("Ruin", 2, 2, 1, 0.0f, 0.0f, 0);		// Ruins
	terrainTypes[3] = new Terrain("Wood", 3, 2, 0, 0.05f, 0.0f, 0);		// Woods
	terrainTypes[4] = new Terrain("Mountain", 4, 3, 0, 0.0f, 0.10f, 0);	// Mountains
	terrainTypes[5] = new Terrain("Water", 5, 4, 0, -0.10f, 0.0f, 1);		// Water
	terrainTypes[6] = new Terrain("Rampart", 6, 2, 1, 0.05f, 0.0f, 0);
	terrainTypes[NUM_TERRAIN] = new Terrain("Blighted Plain", 7, 1, 0, 0.0f, 0.05f, -1);
	terrainTypes[NUM_TERRAIN + 1] = new Terrain("Blighted Badland", 8, 2, 0, 0.0f, 0.05f, -1);
	terrainTypes[NUM_TERRAIN + 2] = new Terrain("Blighted Ruin", 9, 2, 1, 0.0f, 0.05f, -1);
	terrainTypes[NUM_TERRAIN + 3] = new Terrain("Blighted Wood", 10, 2, 0, 0.05f, 0.05f, -1);
	terrainTypes[NUM_TERRAIN + 4] = new Terrain("Blighted Mountain", 11, 3, 0, 0.0f, 0.15f, -1);
	terrainTypes[NUM_TERRAIN + 5] = new Terrain("Blighted Water", 12, 4, 0, -0.10f, 0.05f, 0);
	terrainTypes[NUM_TERRAIN + 6] = new Terrain("Blighted Rampart", 13, 2, 1, 0.05f, 0.05f, -1);
	terrainTypes[NUM_TERRAIN * 2] = new Terrain("Holy Plain", 14, 1, 0, 0.0f, -0.05f, 1);
	terrainTypes[NUM_TERRAIN * 2 + 1] = new Terrain("Holy Badland", 15, 2, 0, 0.0f, -0.05f, 1);
	terrainTypes[NUM_TERRAIN * 2 + 2] = new Terrain("Holy Ruin", 16, 2, 1, 0.0f, -0.05f, 1);
	terrainTypes[NUM_TERRAIN * 2 + 3] = new Terrain("Holy Wood", 17, 2, 0, 0.05f, -0.05f, 1);
	terrainTypes[NUM_TERRAIN * 2 + 4] = new Terrain("Holy Mountain", 18, 3, 0, 0.0f, 0.05f, 1);
	terrainTypes[NUM_TERRAIN * 2 + 5] = new Terrain("Holy Water", 19, 4, 0, -0.10f, -0.05f, 2);
	terrainTypes[NUM_TERRAIN * 2 + 6] = new Terrain("Holy Rampart", 20, 2, 1, 0.05f, -0.05f, 1);


	//	--	Set up adjacencies	--

	// Plains adjacent to plains, badlands, ruins, woods, water, ramparts
	int adj_Plains[] = {0, 1, 2, 3, 5, 6,
		 (NUM_TERRAIN), (NUM_TERRAIN + 1), (NUM_TERRAIN + 2), (NUM_TERRAIN + 3), (NUM_TERRAIN + 5), (NUM_TERRAIN + 6),
		 (NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 5), (NUM_TERRAIN * 2 + 6)};
	vector<int> plains (adj_Plains, adj_Plains + sizeof(adj_Plains) / sizeof(int));
	terrainTypes[0]->adjacencyList = plains;
	
	// Badlands adjacent to plains, badlands, ruins, mountains
	int adj_Badlands[] = {0, 1, 2, 4,
		(NUM_TERRAIN), (NUM_TERRAIN + 1), (NUM_TERRAIN + 2), (NUM_TERRAIN + 4),
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 4)};
	vector<int> badlands (adj_Badlands, adj_Badlands + sizeof(adj_Badlands) / sizeof(int));
	terrainTypes[1]->adjacencyList = badlands;
	
	// Ruins adjacent to plains, badlands, ruins, woods, ramparts
	int adj_Ruins[] = {0, 1, 2, 3, 6,
		(NUM_TERRAIN), (NUM_TERRAIN + 1), (NUM_TERRAIN + 2), (NUM_TERRAIN + 3), (NUM_TERRAIN + 6),
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4)};
	vector<int> ruins (adj_Ruins, adj_Ruins + sizeof(adj_Ruins) / sizeof(int));
	terrainTypes[2]->adjacencyList = ruins;
	
	// Woods adjacent to plains, woods, ruins, mountains, water
	int adj_Woods[] = {0, 2, 3, 4, 5,
		(NUM_TERRAIN), (NUM_TERRAIN + 2), (NUM_TERRAIN + 3), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5),
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5)};
	vector<int> woods (adj_Woods, adj_Woods + sizeof(adj_Woods) / sizeof(int));
	terrainTypes[3]->adjacencyList = woods;
	
	// Mountains adjacent to badlands, woods, mountains, water, ramparts
	int adj_Mountains[] = {1, 3, 4, 5, 6,
		(NUM_TERRAIN + 1), (NUM_TERRAIN + 3), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5), (NUM_TERRAIN + 6),
		(NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5), (NUM_TERRAIN * 2 + 6)};
	vector<int> mountains (adj_Mountains, adj_Mountains + sizeof(adj_Mountains) / sizeof(int));
	terrainTypes[4]->adjacencyList = mountains;
	
	// Water adjacent to plains, woods, mountains, water, ramparts
	int adj_Water[] = {0, 3, 4, 5, 6,
		(NUM_TERRAIN), (NUM_TERRAIN + 3), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5), (NUM_TERRAIN + 6),
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5), (NUM_TERRAIN * 2 + 6)};
	vector<int> water (adj_Water, adj_Water + sizeof(adj_Water) / sizeof(int));
	terrainTypes[5]->adjacencyList = water;
	
	// Ramparts adjacent to plains, woods, mountains, water
	int adj_Ramparts[] = {0, 2, 4, 5,
		(NUM_TERRAIN), (NUM_TERRAIN + 2), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5),
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5)};
	vector<int> ramparts (adj_Ramparts, adj_Ramparts + sizeof(adj_Ramparts) / sizeof(int));
	terrainTypes[6]->adjacencyList = ramparts;
	
	//	--	Blighted Terrain	--	Same adjacencies as above, except with no holy terrain	--
	int adj_Blighted_Plains[] = {0, 1, 2, 3, 5, 6,
		(NUM_TERRAIN), (NUM_TERRAIN + 1), (NUM_TERRAIN + 2), (NUM_TERRAIN + 3), (NUM_TERRAIN + 5), (NUM_TERRAIN + 6)};
	vector<int> blighted_plains (adj_Blighted_Plains, adj_Blighted_Plains + sizeof(adj_Blighted_Plains) / sizeof(int));
	terrainTypes[7]->adjacencyList = blighted_plains;
	
	int adj_Blighted_Badlands[] = {0, 1, 2, 4,
		(NUM_TERRAIN), (NUM_TERRAIN + 1), (NUM_TERRAIN + 2), (NUM_TERRAIN + 4)};
	vector<int> blighted_badlands (adj_Blighted_Badlands, adj_Blighted_Badlands + sizeof(adj_Blighted_Badlands) / sizeof(int));
	terrainTypes[8]->adjacencyList = blighted_badlands;
	
	int adj_Blighted_Ruins[] = {0, 1, 2, 3, 6,
		(NUM_TERRAIN), (NUM_TERRAIN + 1), (NUM_TERRAIN + 2), (NUM_TERRAIN + 3), (NUM_TERRAIN + 6)};
	vector<int> blighted_ruins (adj_Blighted_Ruins, adj_Blighted_Ruins + sizeof(adj_Blighted_Ruins) / sizeof(int));
	terrainTypes[9]->adjacencyList = blighted_ruins;
	
	int adj_Blighted_Woods[] = {0, 2, 3, 4, 5,
		(NUM_TERRAIN), (NUM_TERRAIN + 2), (NUM_TERRAIN + 3), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5)};
	vector<int> blighted_woods (adj_Blighted_Woods, adj_Blighted_Woods + sizeof(adj_Blighted_Woods) / sizeof(int));
	terrainTypes[10]->adjacencyList = blighted_woods;
	
	int adj_Blighted_Mountains[] = {1, 3, 4, 5, 6,
		(NUM_TERRAIN + 1), (NUM_TERRAIN + 3), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5), (NUM_TERRAIN + 6)};
	vector<int> blighted_mountains (adj_Blighted_Mountains, adj_Blighted_Mountains + sizeof(adj_Blighted_Mountains) / sizeof(int));
	terrainTypes[11]->adjacencyList = blighted_mountains;
	
	int adj_Blighted_Water[] = {0, 3, 4, 5, 6,
		(NUM_TERRAIN), (NUM_TERRAIN + 3), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5), (NUM_TERRAIN + 6)};
	vector<int> blighted_water (adj_Blighted_Water, adj_Blighted_Water + sizeof(adj_Blighted_Water) / sizeof(int));
	terrainTypes[12]->adjacencyList = blighted_water;
	
	int adj_Blighted_Ramparts[] = {0, 2, 4, 5,
		(NUM_TERRAIN), (NUM_TERRAIN + 2), (NUM_TERRAIN + 4), (NUM_TERRAIN + 5)};
	vector<int> blighted_ramparts (adj_Blighted_Ramparts, adj_Blighted_Ramparts + sizeof(adj_Blighted_Ramparts) / sizeof(int));
	terrainTypes[13]->adjacencyList = blighted_ramparts;
	
	//	--	Holy Terrain	--	Same adjacencies as original, except with no blighted terrain	--
	int adj_Holy_Plains[] = {0, 1, 2, 3, 5, 6,
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 6)};
	vector<int> holy_plains (adj_Holy_Plains, adj_Holy_Plains + sizeof(adj_Holy_Plains) / sizeof(int));
	terrainTypes[14]->adjacencyList = holy_plains;
	
	int adj_Holy_Badlands[] = {0, 1, 2, 4,
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 4)};
	vector<int> holy_badlands (adj_Holy_Badlands, adj_Holy_Badlands + sizeof(adj_Holy_Badlands) / sizeof(int));
	terrainTypes[15]->adjacencyList = holy_badlands;
	
	int adj_Holy_Ruins[] = {0, 1, 2, 3, 6,
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 6)};
	vector<int> holy_ruins (adj_Holy_Ruins, adj_Holy_Ruins + sizeof(adj_Holy_Ruins) / sizeof(int));
	terrainTypes[16]->adjacencyList = holy_ruins;
	
	int adj_Holy_Woods[] = {0, 2, 3, 4, 5,
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5)};
	vector<int> holy_woods (adj_Holy_Woods, adj_Holy_Woods + sizeof(adj_Holy_Woods) / sizeof(int));
	terrainTypes[17]->adjacencyList = holy_woods;
	
	int adj_Holy_Mountains[] = {1, 3, 4, 5, 6,
		(NUM_TERRAIN * 2 + 1), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5), (NUM_TERRAIN * 2 + 6)};
	vector<int> holy_mountains (adj_Holy_Mountains, adj_Holy_Mountains + sizeof(adj_Holy_Mountains) / sizeof(int));
	terrainTypes[18]->adjacencyList = holy_mountains;
	
	int adj_Holy_Water[] = {0, 3, 4, 5, 6,
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 3), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5), (NUM_TERRAIN * 2 + 6)};
	vector<int> holy_water (adj_Holy_Water, adj_Holy_Water + sizeof(adj_Holy_Water) / sizeof(int));
	terrainTypes[19]->adjacencyList = holy_water;
	
	int adj_Holy_Ramparts[] = {0, 2, 4, 5,
		(NUM_TERRAIN * 2), (NUM_TERRAIN * 2 + 2), (NUM_TERRAIN * 2 + 4), (NUM_TERRAIN * 2 + 5)};
	vector<int> holy_ramparts (adj_Holy_Ramparts, adj_Holy_Ramparts + sizeof(adj_Holy_Ramparts) / sizeof(int));
	terrainTypes[20]->adjacencyList = holy_ramparts;


	// Setup random number generator
	srand(time(NULL));	// Setup the first seed
	unsigned int firstSeed = rand();
	srand(firstSeed);	// Setup the second seed

	// Build map
	for (int i = 0; i < mapWidth; ++i)
	{
		for (int j = 0; j < mapHeight; ++j)
		{
			int terrain;
			if (i == 0)
			{
				if (j == 0)
				{
					terrain = rand() % 6;				// Random number between 0 and 6

					int blighted = rand() % 100 + 1;	// Random number between 1 and 100
					int holy = rand() % 100 + 1;
					if (blighted <= 33)					// 33% chance of being blighted
						terrain += NUM_TERRAIN;
					else if (holy <= 20)				// 20% chance of being holy
						terrain += NUM_TERRAIN * 2;

				}
				else
				{
					Terrain* upTrn = dynamic_cast<Terrain*>(map[i][j-1]);				// Get the terrain immediately above
					
					terrain = rand() % static_cast<int>(upTrn->adjacencyList.size());	// Random number between 0 and the last element of the list

					if (terrain > 13)		// If it's holy
					{
						int holy = rand() % 100 + 1;
						if (holy <= 80)		// 80% chance to make it "unholy" (simulating the 20% chance to be holy)
							terrain -= NUM_TERRAIN * 2;
					}
					else if (terrain > 6)	// If it's blighted
					{
						int blighted = rand() % 100 + 1;	// Random number between 1 and 100
						if (blighted <= 67)
							terrain -= NUM_TERRAIN;
					}
				}
			}
			else
			{
				if (j == 0)		// Only worried about terrain to the left
				{
					Terrain* leftTrn = dynamic_cast<Terrain*>(map[i-1][j]);
					
					terrain = rand() % static_cast<int>(leftTrn->adjacencyList.size());	// Random number between 0 and the last element of the list

					if (terrain > 13)		// If it's holy
					{
						int holy = rand() % 100 + 1;
						if (holy <= 80)		// 80% chance to make it "unholy" (simulating the 20% chance to be holy)
							terrain -= NUM_TERRAIN * 2;
					}
					else if (terrain > 6)	// If it's blighted
					{
						int blighted = rand() % 100 + 1;	// Random number between 1 and 100
						if (blighted <= 67)
							terrain -= NUM_TERRAIN;
					}
				}
				else	// Have to make adjacency list based on grid elements above & to the elfft
				{
					Terrain* upTrn = dynamic_cast<Terrain*>(map[i][j-1]);
					Terrain* leftTrn = dynamic_cast<Terrain*>(map[i-1][j]);
					
					vector<int> intersectionList;
					intersectionList.resize(1);		// Start with at least one intersection
					vector<int> upList = upTrn->adjacencyList;
					vector<int> leftList = leftTrn->adjacencyList;


					// Find the set intersection
					bool foundMatch = false;

					for (size_t i = 0; i < upList.size(); ++i)
					{
						for (size_t j = i; j < leftList.size() && foundMatch == false; ++j)
						{
							if (leftList[j] == upList[i])	// This avoids repeats because both arrays are already sorted
							{
								intersectionList.push_back(leftList[j]);
								foundMatch = true;		// Only one match per inner loop, exit as soon as you find one
								// Could also just use a break but NEVER
							}
						}
						foundMatch = false;
					}
					//cout << intersectionList.size();
					terrain = rand() % static_cast<int>(intersectionList.size());	// Random number between 0 and the last element of the list

					if (terrain > 13)	// If it's holy
					{
						int holy = rand() % 100 + 1;
						if (holy <= 80)		// 80% chance to make it "unholy" (simulating the 20% chance to be holy)
							terrain -= NUM_TERRAIN * 2;
					}
					else if (terrain > 6)	// If it's blighted
					{
						int blighted = rand() % 100 + 1;	// Random number between 1 and 100
						if (blighted <= 67)
							terrain -= NUM_TERRAIN;
					}
				}
			}

			map[i][j] = new Terrain(terrainTypes[terrain]);
		}	// End of inner for
	}	// End of outer for

	return map;
}