#ifndef GameMap_H
#define GameMap_H

//	--	Include Statements	--

#include <vector>

#include "Terrain.h"

//	--	End Include Statements	--

class GameMap
{

	//	--	Constructors/Destructors	--

public:
	GameMap(void);
	~GameMap(void);

	//	--	End Constructors/Destructors	--


	//	--	Methods	--
	
	vector< vector<GamePiece*> > ConstructMap(int mapWdt, int mapHgt);

	//	--	End Methods	--

};

#endif