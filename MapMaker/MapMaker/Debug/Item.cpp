#include "Item.h"

/// Local function
std::string ParseForTab(std::string input)
{
	while (input.substr(input.length() - 1, 1) == "\t")		// While the trailing character is a tab
		input = input.substr(0, input.length() - 1);	// Shave tab off
	
	return input;
}

// TODO: Setup constructors/Destructors
Item::Item(void)
{
}

Item::Item(int item_Type, string item_Name, string item_Desc)
{
	itemType = item_Type;
	itemName = ParseForTab(item_Name);
	itemDesc = ParseForTab(item_Desc);

	modifiers = NULL;
	wpnInfo = NULL;
	amrInfo = NULL;
	shdInfo = NULL;
	cnsInfo = NULL;
}


Item::~Item(void)
{
}


void Item::SetWeapon(int wType, int aType, int dmg)
{
	wpnInfo = new WeaponInfo;
	wpnInfo->weaponType = wType;
	wpnInfo->attackType = aType;
	wpnInfo->damage = dmg;
}

void Item::SetArmor(int aType, int def)
{
	amrInfo = new ArmorInfo;
	amrInfo->armorType = aType;
	amrInfo->armorMod = def;
}

void Item::SetShield(float reduction)
{
	shdInfo = new ShieldInfo;
	shdInfo->dmgReduction = reduction;
}

void Item::SetConsumable(int cType, int uses)
{
	cnsInfo = new ConsumableInfo;
	cnsInfo->consumableType = cType;
	cnsInfo->numUses = uses;
}

void Item::SetModifiers(unordered_map<string, string> newModifiers)
{
	if (modifiers == NULL)
	{
		modifiers = new Special();
	}

	for(std::unordered_map<string, string>::iterator iter = newModifiers.begin(); iter != newModifiers.end(); ++iter)	// Black voodoo
	{
		string key = iter->first;
		string val = iter->second;

		int modIndex = StringToNumber<int>(key);

		int index = val.find('.');	// Is it a decimal
		if (index == -1)			// It's an integer
		{
			int modVal = StringToNumber<int>(val);
			modifiers->SetMod(modIndex, modVal);
		}
		else
		{
			float modVal = StringToNumber<float>(val);
			modifiers->SetMod(modIndex, modVal);
		}
	}// End of for
}
