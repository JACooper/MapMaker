#ifndef Terrain_H
#define Terrain_H

using namespace std;

//	--	Include Statements	--

#include <string>
#include <vector>
#include <iostream>

#include "GamePiece.h"


//	--	End Include Statements	--

class Terrain : public GamePiece
{
	//	--	Class Variables	--

public:
//protected:
	
	// Terrain attributes
	string trnName;
	int trnIndex;
	int moveCost;			// Move cost of 0 means the terrain is impassable

	// Combat modifiers
	//	Affect defender
	int defMod;
	float dodgeMod;
	//	Affect attacker
	int atkMod;			// Unsure this will ever see use
	float accMod;
	float critMod;

	// Health modifiers
	int healRate;		// Can be negative, damaging units instead

//public:
	vector<int> adjacencyList;

	//	--	End Class Variables	--


	//	--	Constructors/Destructors	--

public:
	Terrain(void);
	Terrain(string terrainName, int index, int mCost, int def, float dod, float crit, int heal);
	Terrain(Terrain* otherTerrain);	// Copy constructor
	~Terrain(void);

	//	--	End Constructors/Destructors	--


	//	--	Methods	--

	void Display();

	//	--	End Methods	--

};

#endif