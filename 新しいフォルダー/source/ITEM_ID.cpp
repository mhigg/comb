#include "ITEM_ID.h"

ITEM_ID operator++(ITEM_ID id)
{
	return static_cast<ITEM_ID>(static_cast<int>(id) + 1);
}

// Žg‚í‚È‚¢