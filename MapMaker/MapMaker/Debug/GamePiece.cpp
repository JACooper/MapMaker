//	--	Include Statements	--

#include "GamePiece.h"

//	--	End of Include Statements	--


//	--	Constructors/Destructors	--

// No Argument Constructor
GamePiece::GamePiece(void)
{
	x = 0;
	y = 0;
}

// Base Constructor
GamePiece::GamePiece(int i, int j)
{
	x = i;
	y = j;
}

// Destructor, as noted by the tilde
GamePiece::~GamePiece(void)
{
	// From what I can tell, the default destructor will be fine unless I have pointers, in which case I'll need to use delete pointerName to properly free up memory
}

//	--	End of Constructors/Destructors	--



//	--	Methods	--

	//	--	Accessor/Mutator Methods	--

	int GamePiece::getX()
	{ return x; }

	void GamePiece::setX(int i)
	{
		if (i >= 0)
			x = i;
	}

	int GamePiece::getY()
	{ return y; }

	void GamePiece::setY(int j)
	{
		if (j >= 0)
			y = j;
	}

	//	--	End of Accessor/Mutator Methods	--

	void GamePiece::Display()
	{

	}

//	--	End of Methods	--