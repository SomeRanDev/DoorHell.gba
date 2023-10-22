#pragma once

#include "bn_regular_bg_ptr.h"

#include "dh/dh_defines.h"

DH_START_NAMESPACE

class camera {
public:
	camera();

	[[nodiscard]] bool update_intro();
	[[nodiscard]] bool should_update_hand_intro() const;

	[[nodiscard]] bool set_position(int _x, int _y);
	void refresh_position();
	[[nodiscard]] bool shift(int _x, int _y);

	static constexpr int world_width = 11;
	static constexpr int world_height = 4;

private:
	bn::regular_bg_ptr _bg;

	int x = 3;
	int y = 3;

	int intro_time = 0;
	int intro_frame = 0;
};

DH_END_NAMESPACE
