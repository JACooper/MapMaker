#include <stdlib.h>
#include <time.h>

#include "Unit.h"

using namespace std;

Unit::Unit(void) : GamePiece(0, 0)
{

}


Unit::Unit(int i, int j) : GamePiece(i, j)
{

}


Unit::Unit(string unit_name, int unit_level, int unit_experience, int unit_str, int unit_agi, int unit_skl, int unit_wlp)
{
	unitName = unit_name;
	level = unit_level;
	experience = unit_experience;
	strength = unit_str;
	agility = unit_agi;
	skill = unit_skl;
	willpower = unit_wlp;

	health = 2 * level + strength + willpower;
	maxHealth = health;

	healRate = 0;		// Maybe have this based off of willpower, and have willpower do nothing for health itself?
	movePoints = (agility * 2) / 3;
	physRes = strength / 2;
	mntlRes = willpower;
	accuracy = 15 + (2 * level) + (10 * skill);
	critChance = skill + (level / 2);
	dodgeChance = (agility * 3) / 2;
	threat = 3 * level + (maxHealth - health);

	occSpace = NULL;
	inventory = new Paperdoll;
}


Unit::~Unit(void)
{
	// The items themselves will be deleted with the inventory
	/*delete inventory->head;
	delete inventory->body;
	delete inventory->weaponHand;
	delete inventory->offHand;
	delete inventory->misc;*/
	delete inventory;
	delete occSpace;
}

bool Unit::IsDead()
{
	bool dead = false;
	if (health <= 0)
		dead = true;

	return dead;
}

void Unit::SetSpace(GamePiece* newSpace)
{
	occSpace = dynamic_cast<Terrain*>(newSpace);

}

void Unit::Display()
{
	cout << " | ";
	if (unitName.length() < 2)
		cout << "_";
	cout << unitName.substr(0,2) << " | "; //(trnName.substr(0, 2));	// Display first 2 letters of name
}

bool Unit::EquipItem(Item* itemToEquip)
{
	bool equipSuccessful = false;
	if (itemToEquip != NULL)
	{
		switch (itemToEquip->itemType)
		{
			case 0:		// Weapon
			{
				if (inventory->weaponHand != NULL)	// Already have an item equipped
				{
					if (inventory->weaponHand->modifiers != NULL)	// It had modifiers
					{
						// Remove modifiers from unit
					}
				}

				if (itemToEquip->modifiers != NULL)		// The new item has modifiers
				{
					// Apply modifiers
				}

				inventory->weaponHand = itemToEquip;
				break;
			}
			case 1:		// Armor
			{
				if (inventory->body != NULL)	// Already have an item equipped
				{
					if (inventory->body->modifiers != NULL)	// It had modifiers
					{
						// Remove modifiers from unit
					}
				}

				if (itemToEquip->modifiers != NULL)		// The new item has modifiers
				{
					// Apply modifiers
				}

				inventory->body = itemToEquip;
				break;
			}
			case 2:		// Helm
			{
				if (inventory->head != NULL)	// Already have an item equipped
				{
					if (inventory->head->modifiers != NULL)	// It had modifiers
					{
						// Remove modifiers from unit
					}
				}

				if (itemToEquip->modifiers != NULL)		// The new item has modifiers
				{
					// Apply modifiers
				}

				inventory->head = itemToEquip;
				break;
			}
			case 3:		// Shield
			{
				if (inventory->offHand != NULL)	// Already have an item equipped
				{
					if (inventory->offHand->modifiers != NULL)	// It had modifiers
					{
						// Remove modifiers from unit
					}
				}

				if (itemToEquip->modifiers != NULL)		// The new item has modifiers
				{
					// Apply modifiers
				}

				inventory->offHand = itemToEquip;
				break;
			}
			case 4:		// Consumable
			{
				if (inventory->misc != NULL)	// Already have an item equipped
				{
					if (inventory->misc->modifiers != NULL)	// It had modifiers
					{
						// Remove modifiers from unit
					}
				}

				if (itemToEquip->modifiers != NULL)		// The new item has modifiers
				{
					// Apply modifiers
				}

				inventory->misc = itemToEquip;
				break;
			}
			case 5:		// Misc
			{
				if (inventory->misc != NULL)	// Already have an item equipped
				{
					if (inventory->misc->modifiers != NULL)	// It had modifiers
					{
						// Remove modifiers from unit
					}
				}

				if (itemToEquip->modifiers != NULL)		// The new item has modifiers
				{
					// Apply modifiers
				}

				inventory->misc = itemToEquip;
				break;
			}
		}// End of switch
	}// End of if
	//else
	//	equipSuccessful = false;

	return equipSuccessful;
}