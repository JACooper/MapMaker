#include "Terrain.h"

Terrain::Terrain(void)
{
}

Terrain::Terrain(string terrainName, int index, int mCost, int def, float dod, float crit, int heal)
{
	trnName = terrainName;
	trnIndex = index;
	moveCost = mCost;
	defMod = def;
	dodgeMod = dod;
	critMod = crit;
	healRate = heal;
}

Terrain::Terrain(Terrain* otherTerrain)
{
	trnName = otherTerrain->trnName;
	trnIndex = otherTerrain->trnIndex;
	moveCost = otherTerrain->moveCost;
	defMod = otherTerrain->defMod;
	dodgeMod = otherTerrain->dodgeMod;
	atkMod = otherTerrain->atkMod;
	accMod = otherTerrain->accMod;
	critMod = otherTerrain->critMod;
	healRate = otherTerrain->healRate;
	adjacencyList = otherTerrain->adjacencyList;
}

Terrain::~Terrain(void)
{
}

void Terrain::Display()
{
	cout << " | ";
	if (trnIndex < 10)
		cout << 0;
	cout << trnIndex << " | "; //(trnName.substr(0, 2));	// Display first 2 letters of name
}