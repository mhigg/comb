#pragma once
// œØÃﬂèÓïÒ

enum class MAP_ID
{
	NONE,			// âΩÇ‡Ç»Çµ
	// œØÃﬂóp
	WALL1,			// ï«
	WALL2,
	WALL3,
	WALL4,
	WALL5,
	WALL6,
	WALL7,
	WALL8,
	WALL9,
	WALL10,
	WALL11,
	WALL12,
	WALL13,
	WALL14,
	WALL15,
	WALL16,
	WALL17,
	WALL18,
	WALL19,
	WALL20,
	WALL21,
	WALL22,			
	WALL23,
	WALL24,
	WALL25,
	WALL26,
	WALL27,
	WALL28,
	WALL29,	
	WALL30,	
	WALL31,
	WALL32,
	WALL33,
	WALL34,
	WALL35,
	WALL36,
	WALL37,		
	WALL38,		
	WALL39,			// è∞
	DOOR1,			// î‡
	DOOR2,
	DOOR3,
	DOOR4,
	// ã§í 
	POTION_1,	// Œﬂ∞ºÆ›
	POTION_2,
	POTION_3,
	POTION_4,
	COIN_1,		// ∫≤›
	COIN_2,
	COIN_3,
	COIN_4,
	KEY_1,			// åÆ
	KEY_2,
	MEAT,			// ì˜
	// ìÆìIµÃﬁºﬁ™
	PLAYER,				// Ãﬂ⁄≤‘∞
	ENEMY,				// ¥»–∞
	// Ω√∞ºﬁï 
	SWORD,		
	SHIELD,
	BOOK,
	GOLD,
	DIA,
	ENEMY_2,
	ENEMY_3,
	MOTH_1,
	MOTH_2,
	MOTH_3,
	MOTH_4,
	// ëÂå^µÃﬁºﬁ™
	TREE_1,			// ñÿ
	TREE_2,
	TREE_3,
	TREE_4,
	HOLL_1,			// à‰åÀ
	HOLL_2,
	HOLL_3,
	HOLL_4,
	STONE_1,			// êŒ
	STONE_2,
	STONE_3,
	STONE_4,
	falest,
	falest2,
	falest3,
	falest4,
	falest5,
	falest6,
	falest7,
	falest8,
	falest9,
	falest10,
	falest11,
	falest12,
	falest13,
	falest14,
	falest15,
	falest16,
	MAX
};

#define ITEM_ID_START MAP_ID::POTION_1
#define ITEM_MAX (static_cast<int>(MAP_ID::MAX) - static_cast<int>(ITEM_ID_START))

MAP_ID operator++(MAP_ID id);