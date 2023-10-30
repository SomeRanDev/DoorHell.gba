#include "dh_game.h"

#include "mj/mj_game_list.h"

namespace {
	constexpr const char* me = "SomeRanDev (Robert Borghese)";

    constexpr bn::string_view code_credits[] = { me };
    constexpr bn::string_view graphics_credits[] = { me };
	constexpr bn::string_view sfx_credits[] = { me, "Amada44", "rubberduck", "GboxMikeFozzy" };
}

MJ_GAME_LIST_ADD(dh::game1)
MJ_GAME_LIST_ADD(dh::game2)

MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
// MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)
