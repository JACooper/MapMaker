#ifndef Unit_H
#define Unit_H

using namespace std;

//	--	Include Statements	--

#include <string>

#include "GamePiece.h"
#include "Item.h"
#include "Terrain.h"
//#include "Special.h"

//	--	End Include Statements	--


//	--	Struct Defintions	--

typedef struct Paperdoll_S
{
	Item* head;			// Helmet
	Item* body;			// Body armor
	Item* weaponHand;	// Right hand weapon
	Item* offHand;		// Left hand weapon (shield)
	Item* misc;			// First aid kit, etc.
}Paperdoll;

typedef struct CombatBundle_S
{
	bool success;		// Attack hit
	int bundleType;		// 0 == heal, 1 == attack, 2 == critical
	int magnitude;
}CombatBundle;

//	--	End Struct Definitions	--

class Unit : public GamePiece
{
	//	--	Class Variables	--

protected:

	string unitName;

	// Experience
	int level;			// Will be used to determine experience gain, threat, and so on
	int experience;		// 100, each level(?)

	//	Primary Attributes
	int strength;		// Affects damage, physical resistance, and health
	int agility;		// Affects movement points and dodge chance
	int skill;			// Affects accuracy and critical chance
	int willpower;		// Affects spells and mental resistance

	//	Derived Attributes
	//int health;		// In base class
	int healRate;
	int movePoints;
	int physRes;
	int mntlRes;
	float accuracy;
	float critChance;
	float dodgeChance;
	int threat;			// Will be used in pathfinding to make units raise or lower attack priority among the AI

	//	Terrain Bonuses
	Terrain* occSpace;

	// Inventory
	Paperdoll* inventory;

	// Special Abilities
	//list<Special> abilities;	// Ignore for now

	//	--	End Class Variables	--



	//	--	Constructors/Destructors	--

public:

	Unit(void);
	Unit(int i, int j);
	Unit(string unit_name, int level, int experience, int strength, int agility, int skill, int willpower);
	~Unit(void);

	//	--	End Constructors/Destructors	--



	//	--	Methods	--

public:

	// ATTACK IS CURRENTLY UNIMPLEMENTED AND HAS BEEN REMOVED FROM THIS VERSION

	///	Attack accepts a GamePiece (either a unit or a container) and a modifier as
	///	parameters and returns a bundle telling if the attack hit and, if so, how much
	///	damage was dealt. This function handles accuracy, critical, and like calculations.
	///
	///	param: target - The GamePiece being attacked
	///	param: modifer - The attack modifier (this is usually 1);
	///
	//void Attack(GamePiece* target, float atkModifier, float defModifier);

	///	Compares the unit's current health value to 0 and returns true if it is less than or equal.
	///
	bool IsDead();

	///	When the unit dies, their inventory drops	-	UNIMPLEMENTED FOR NOW
	///
	//list<Item> DropInventory();
	
	///	Sets unit's terrain variable
	///
	///	param: newSpace - A pointer to a terrain piece
	///
	void SetSpace(GamePiece* newSpace);

	///	Displays the unit to the screen (currently just the first two letters of their name)
	///
	void Display();
	
	///	Equips an item
	///
	/// param: itemToEquip - The item to be equipped
	///
	bool EquipItem(Item* itemToEquip);

	//	--	End Methods	--
};

#endif