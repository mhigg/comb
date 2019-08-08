#include "MAP_ID.h"

MAP_ID operator++(MAP_ID id)
{
	return static_cast<MAP_ID>(static_cast<int>(id) + 1);
}
