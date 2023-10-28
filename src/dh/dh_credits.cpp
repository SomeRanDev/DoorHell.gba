#include "dh_game.h"

#include "mj/mj_game_list.h"

namespace {
    constexpr bn::string_view code_credits[] = { "SomeRanDev (Robert Borghese)" };
    constexpr bn::string_view graphics_credits[] = { "SomeRanDev (Robert Borghese)" };
	constexpr bn::string_view sfx_credits[] = { "SomeRanDev (Robert Borghese)", "Amada44" };
}

// Add it twice since it contains two micro games (if this is not allowed, feel free to delete!)
MJ_GAME_LIST_ADD(dh::game)
MJ_GAME_LIST_ADD(dh::game)

MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
// MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)