#pragma once

#include "bn_sprite_ptr.h"
#include "bn_fixed.h"

#include "dh_defines.h"

DH_START_NAMESPACE

class hand {
public:
	hand();

	void add_x(bn::fixed x);
	void add_y(bn::fixed y);

	void update();
	void update_normal();
	void update_press();

	void update_movement();

	void set_frame(int frame);

	void press();
	bool is_actively_pressing() const;

	bn::sprite_ptr hand_sprite;

	int time = 0;
	int frame = 0;

	int is_pressing = 0;
};

DH_END_NAMESPACE
