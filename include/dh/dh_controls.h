#pragma once

#include "dh/dh_defines.h"

#include "bn_optional.h"
#include "bn_sprite_ptr.h"

DH_START_NAMESPACE

class controls {
public:
	controls(bool is_part_2);

private:
	bn::sprite_ptr control_pad;
	bn::sprite_ptr a_button;
	bn::optional<bn::sprite_ptr> b_button;

	bn::optional<bn::sprite_ptr> up_sprite;
	bn::optional<bn::sprite_ptr> down_sprite;
	bn::optional<bn::sprite_ptr> left_sprite;
	bn::optional<bn::sprite_ptr> right_sprite;

	bn::optional<bn::sprite_ptr> a_sprite;
	bn::optional<bn::sprite_ptr> b_sprite;
};

DH_END_NAMESPACE
