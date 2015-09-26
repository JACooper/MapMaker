#ifndef GamePiece_H
#define GamePiece_H

class GamePiece
{
	//	--	Class Variables	--

protected:
	int x, y;
	int health;
	int maxHealth;

	//	--	End Class Variables	--



	//	--	Constructors/Destructors	--

public:
	GamePiece(void);
	GamePiece(int i, int j);
	virtual ~GamePiece(void);	// Virtual as a benign way to make GamePiece polymorphic

	//	--	End Constructors/Destructors	--



	//	--	Methods	--
	
	///
	///
	virtual void Display();

	///	
	///
	int getX();

	///	
	///
	void setX(int i);

	///	
	///
	int getY();

	///	
	///
	void setY(int j);

	//	--	End Methods	--
};

#endif