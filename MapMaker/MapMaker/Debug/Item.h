#ifndef Item_H
#define Item_H

//	--	Include Statements	--

#include <string>
#include <unordered_map>
#include <sstream>

#include "Special.h"

//	--	End Include Statements	--

using namespace std;


///	Nabbed from the cplusplus forums. Thanks Bazzy!
///
template <typename T>
T StringToNumber ( const string &Text )	//Text not by const reference so that the function can be used with a 
{										//character array as argument
	istringstream ss(Text);
	T result;
	return ss >> result ? result : -1;	// Return -1 if read failed
}


//	--	Struct Definitions	--

typedef struct WeaponInfo_S
{
	int weaponType;		// 0 == One handed, 1 == Two handed, 2 == longbow, 3 == crossbow, etc.
	int attackType;		// 0 == heal, 1 == slashing, 2 == bludgeoning, 3 == piercing
	int damage;
	//int durability;
}WeaponInfo;

typedef struct ArmorInfo_S
{
	int armorType;	// 0 == unarmored, 1 == lightly armored, 2 == medium armor, 3 == heavy armor
	int armorMod;
}ArmorInfo;

typedef struct ShieldInfo_S
{
	//int shieldType;	// UNIMPLEMENTED
	float dmgReduction;
}ShieldInfo;

typedef struct ConsumableInfo_S
{
	int consumableType;	// 0 == health item, 1 == throwing item, etc.
	int numUses;
}ConsumableInfo;

//	--	End Struct Definitions	--


class Item
{
	//	--	Class Variables	--

public:
	int itemType;		// 0 == weapon, 1 == armor, 2 == helmet, 3 == shield, 4 == consumable, 5 == misc
	string itemName;
	string itemDesc;
	
	Special* modifiers;

	// All but one of these will be NULL
	WeaponInfo* wpnInfo;
	ArmorInfo* amrInfo;
	ShieldInfo* shdInfo;
	ConsumableInfo* cnsInfo;

	//	--	End Class Variables	--



	//	--	Constructors/Destructors	--

public:
	Item(void);
	Item(int item_Type, string item_Name, string item_Desc);
	~Item(void);

	//	--	End Constructors/Destructors	--



	//	--	Methods	--

	void SetWeapon(int wType, int aType, int dmg);
	
	void SetArmor(int aType, int def);

	void SetShield(float reduction);

	void SetConsumable(int cType, int uses);

	void SetModifiers(unordered_map<string, string> modifiers);

	//	--	End Methods	--
};

#endif Item_H