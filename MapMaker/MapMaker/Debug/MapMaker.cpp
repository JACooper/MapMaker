// MapMaker.cpp : Defines the entry point for the console application.
//

using namespace std;

//	--	Include Statements	--

#include <iostream>
#include <fstream>
#include <unordered_map>

#include <vector>		// For map and unit lists
#include <stdlib.h>
#include <time.h>		// For random number generation

#include "Unit.h"		// Includes GamePiece, Item, Vector2, and Unit (will include Special at a later date)
#include "Terrain.h"	// Includes GamePiece, Terrain
#include "GameMap.h"

//	--	End Include Statements	--

//	--	Variables	--

vector< vector<GamePiece*> > trnMap;
vector<Unit*> playerParty;
//vector<Unit*> enemiesParty;
vector<Item*> itemDatabase;			// This will likely get large enough for it to be worth changing to a hashtable later

//	--	End Variables	--

//	--	Functions	--

///	Searches a string for a comment symbol, and removes comment from string if it exists.
///	Should be changed to accept a character to parse on, as opposed to the fixed "$".
///
///	param: input - String to search for a character within.
///
std::string ParseForComment(std::string input)
{
	string parsed;
	int index = input.find('$');			// Look for comment
	if (index != -1)						// If there was a comment
		parsed = input.substr(0, index);	// Parse it out
	else
		parsed = input;

	return parsed;
}


///	Reads in the item database.
/// Currently the database is a text file - should it change to a binary file, the stream will have to change accordingly.
///
///	param: filename - String representing the path of the database file.
///
bool ReadItems(string filename)
{
	bool readSuccessfully = true;

	ifstream itemStream;

	itemStream.open(filename, std::ifstream::in);	// When I eventually change this, a binary file is std::ifstream::binary

	if (!itemStream.is_open())						// If there was an issue opening the stream, quit
		readSuccessfully = false;
	else
	{
		Item* nextItem;

		string input;
		while ( std::getline(itemStream, input) )	// Read entire line	-	I believe this returns NULL at EOF
		{
			string parsed;

			std::getline(itemStream, input);		// Read in item type (The previous getline just discards index, it's useless right now)
			parsed = ParseForComment(input);
			int itemType = StringToNumber<int>(parsed);
			
			std::getline(itemStream, input);		// Read in item name
			parsed = ParseForComment(input);
			string itemName = parsed;
			
			std::getline(itemStream, input);		// Read in item desc
			parsed = ParseForComment(input);
			string itemDescription = parsed;

			nextItem = new Item(itemType, itemName, itemDescription);	// Create the item

			// Check for modifiers - there can be an arbitrary number of these
			bool hasModifiers = false;
			std::getline(itemStream, input);		// Read in item modifiers/first attribute
			int index = input.find(':');			// Look for modifiers
			if (index != -1)						// If you found a :, there are modifiers
				hasModifiers = true;

			if (hasModifiers == true)
			{
				// Set up modifier list
				unordered_map<string, string> modifierDict;
				input = ParseForComment(input);
				string modifier = input;
				int commaIndex = modifier.find(',');
				if (commaIndex == -1)				// There's only one modifier
				{
					string key = input.substr(0, index);
					string val = input.substr(index + 1, input.length() - 2);
					modifierDict[key] = val;
				}
				else
				{
					while (commaIndex != -1)						// While there's at least one modifier to read
					{
						modifier = input.substr(0, commaIndex);		// Grab modifier pair
						index = modifier.find(':');					// Ensure colon index is where it should be

						string key = modifier.substr(0, index);
						string val = modifier.substr(index + 1, (commaIndex - index - 1));	// This seems to ignore trailing whitespace
						modifierDict[key] = val;
						
						input = input.substr(commaIndex + 1, input.length() - commaIndex);	// Remove modifier from string
						commaIndex = input.find(',');
					}
				}

				nextItem->SetModifiers(modifierDict);				// Add modifier to list

				std::getline(itemStream, input);
			}

			// Read in item data
			switch (itemType)
			{
				case 0:		// Weapon
				{
					int wpnType;
					int atkType;
					int wpnDmg;

					//std::getline(itemStream, input);		// Read in weapon type
					parsed = ParseForComment(input);
					wpnType = StringToNumber<int>(parsed);
					
					std::getline(itemStream, input);		// Read in attack type
					parsed = ParseForComment(input);
					atkType = StringToNumber<int>(parsed);
					
					std::getline(itemStream, input);		// Read in damage
					parsed = ParseForComment(input);
					wpnDmg = StringToNumber<int>(parsed);

					nextItem->SetWeapon(wpnType, atkType, wpnDmg);
					break;
				}
				case 1:		// Armor
				{
					int amrType;
					int amrDef;
					
					//std::getline(itemStream, input);		// Read in amor type
					parsed = ParseForComment(input);
					amrType = StringToNumber<int>(parsed);
					
					std::getline(itemStream, input);		// Read in defense mod
					parsed = ParseForComment(input);
					amrDef = StringToNumber<int>(parsed);
					
					nextItem->SetArmor(amrType, amrDef);
					break;
				}
				case 2:		// Helmet	-	Kind of feel like "helmet" should be a property of armor info, rather than it's own type
				{
					int amrType;
					int amrDef;
					
					//std::getline(itemStream, input);		// Read in armor type
					parsed = ParseForComment(input);
					amrType = StringToNumber<int>(parsed);
					
					std::getline(itemStream, input);		// Read in defense mod
					parsed = ParseForComment(input);
					amrDef = StringToNumber<int>(parsed);
					
					nextItem->SetArmor(amrType, amrDef);
					break;
				}
				case 3:		// Shield
				{
					float reduc;
					
					//std::getline(itemStream, input);		// Read in damage reduction
					parsed = ParseForComment(input);
					reduc = StringToNumber<float>(parsed);
					
					nextItem->SetShield(reduc);
					break;
				}
				case 4:		// Consumable
				{
					int cType = 0;			// CONSUMABLES ARE UNIMPLEMENTED AS OF YET
					int uses = 0;

					nextItem->SetConsumable(cType, uses);
					break;
				}
				/*case 5:		// Misc (e.g. necklace)
				{

				}*/
			}	// End of switch

			itemDatabase.push_back(nextItem);
			
			std::getline(itemStream, input);		// Eat trailing space

		}	// End of while

	}

	return readSuccessfully;
}


///	Reads in the player unit database
///	As above, the database is currently a text file, and will likely be changed at some point
///
///	param: filename - String representing he path of the database file.
///
bool ReadPlayerUnits(string filename)
{
	bool readSuccessfully = true;
	
	ifstream unitStream;

	unitStream.open(filename, std::ifstream::in);	// When I eventually change this, a binary file is std::ifstream::binary

	if (!unitStream.is_open())						// If there was an issue opening the stream, quit
		readSuccessfully = false;
	else
	{
		Unit* nextPlayer;

		string input;
		while ( std::getline(unitStream, input) )	// Read entire line	-	I believe this returns NULL at EOF
		{
			string parsed;

			std::getline(unitStream, input);		// Read in unit name (The previous getline just discards index, it's useless right now)
			parsed = ParseForComment(input);
			string unitName = parsed;
			
			std::getline(unitStream, input);		// Read in unit level
			parsed = ParseForComment(input);
			int unitLevel = StringToNumber<int>(parsed);
			
			std::getline(unitStream, input);		// Read in unit experience
			parsed = ParseForComment(input);
			int unitExp = StringToNumber<int>(parsed);
			
			std::getline(unitStream, input);		// Read in unit strength
			parsed = ParseForComment(input);
			int unitStr = StringToNumber<int>(parsed);
			
			std::getline(unitStream, input);		// Read in unit agility
			parsed = ParseForComment(input);
			int unitAgi = StringToNumber<int>(parsed);
			
			std::getline(unitStream, input);		// Read in unit skill
			parsed = ParseForComment(input);
			int unitSkl = StringToNumber<int>(parsed);
			
			std::getline(unitStream, input);		// Read in unit willpower
			parsed = ParseForComment(input);
			int unitWlp = StringToNumber<int>(parsed);
			

			// Create unit
			nextPlayer = new Unit(unitName, unitLevel, unitExp, unitStr, unitAgi, unitSkl, unitWlp);

			std::getline(unitStream, input);		// Read in helmet equip slot index
			parsed = ParseForComment(input);
			int helmIndex = StringToNumber<int>(parsed);
			Item* helmet = NULL;
			if (helmIndex != -1)
				helmet = itemDatabase[helmIndex];
			nextPlayer->EquipItem(helmet);

			std::getline(unitStream, input);		// Read in armor equip slot index
			parsed = ParseForComment(input);
			int amrIndex = StringToNumber<int>(parsed);
			Item* armor = NULL;
			if (amrIndex != -1)
				armor = itemDatabase[amrIndex];
			nextPlayer->EquipItem(armor);
			
			std::getline(unitStream, input);		// Read in weapon hand equip slot index
			parsed = ParseForComment(input);
			int wpnIndex = StringToNumber<int>(parsed);
			Item* weapon = NULL;
			if (wpnIndex != -1)
				weapon = itemDatabase[wpnIndex];
			nextPlayer->EquipItem(weapon);
			
			std::getline(unitStream, input);		// Read in offhand equip slot index
			parsed = ParseForComment(input);
			int offIndex = StringToNumber<int>(parsed);
			Item* offhand = NULL;
			if (offIndex != -1)
				offhand = itemDatabase[offIndex];
			nextPlayer->EquipItem(offhand);
			
			std::getline(unitStream, input);		// Read in offhand equip slot index
			parsed = ParseForComment(input);
			int miscIndex = StringToNumber<int>(parsed);
			Item* misc = NULL;
			if (miscIndex != -1)
				misc = itemDatabase[miscIndex];
			nextPlayer->EquipItem(misc);

			playerParty.push_back(nextPlayer);		// Add player to list

			std::getline(unitStream, input);		// Eat trailing space
		}// End of While
	}

	return readSuccessfully;
}

/// Cleanup function to clear out all assigned pointers
///
void FreeMem()
{
	unsigned int i, j;
	// Free map
	for (i = 0; i < trnMap.size(); ++i)
	{
		for (j = 0; j < trnMap[i].size(); ++j)
		{
			if (trnMap[i][j] != NULL)
				delete trnMap[i][j];
		}
	}

	// Free player list		-	Unnecessary, as they are taken care of by the map deletion
	/*for (i = 0; i < playerParty.size(); ++i)
	{
		if (playerParty[i] != NULL)
			delete playerParty[i];			// Will call Unit destructor
	}*/
	
	// Free item database
	for (i = 0; i < itemDatabase.size(); ++i)
	{
		if (itemDatabase[i] != NULL)
			delete itemDatabase[i];			// Will call Item destructor
	}
}

///	Runs code to create & display map
///
int main(void)
{
	// Setup map
	int mapWidth = 10;
	int mapHeight = 7;
	
	// Create map
	GameMap mapContainer;
	trnMap = mapContainer.ConstructMap(mapWidth, mapHeight);

	/*
	Generate random alphanumeric character.
	For first row, check previous character for other valid characters to write. Randomly generate an alphanumeric character based off this list.
	For subsequent rows, generate an alphanumeric character based on characters to the left and above.
	*/

	if (ReadItems("Debug\\item_database.txt") == false)
	{
		cout << "There was an issue initializing the item database." << endl;
		return 1;	// Don't bother continuing, exit with error code
	}
	if (ReadPlayerUnits("Debug\\unit_database.txt") == false)
	{
		cout << "There was an issue initializing the unit database." << endl;
		return 1;
	}
	
	// Setup random number generator
	std::srand(time(NULL));	// Setup the first seed
	unsigned int firstSeed = rand();
	std::srand(firstSeed);	// Setup the second seed

	int x, y;
	
	// Place units on map
	for (size_t i = 0; i < playerParty.size(); ++i)
	{
		x = rand() % mapWidth;
		y = rand() % mapHeight;
		playerParty[i]->setX(x);
		playerParty[i]->setY(y);
		playerParty[i]->SetSpace(trnMap[x][y]);
		trnMap[x][y] = playerParty[i];
	}

	// Setup logic (i.e. turns, pre-play pathfinding, etc.)
	bool keepExecuting = true;
	bool playerTurn = true;

	for (int i = 0; i < mapWidth; ++i)
		cout << "   --   ";	// Display border
	cout << endl;
	// Display map
	for (int j = 0; j < mapHeight; ++j)
	{
		for (int i = 0; i < mapWidth; ++i)
			trnMap[i][j]->Display();
		cout << endl;							// Move to next row
		for (int i = 0; i < mapWidth; ++i)
			cout << "   --   ";					// Display border
		cout << endl;
	}

	FreeMem();

	cout << "\nEnter any key to exit: ";
	string input;				
	std::cin >> input;
	
	return 0;
}

//	--	End Functions	--