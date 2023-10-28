#pragma once

#include "bn_fixed.h"
#include "bn_random.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

#include "dh/dh_defines.h"

DH_START_NAMESPACE

class candy {
public:
	candy();

	[[nodiscard]] inline bn::fixed x() const { return candy_sprite.x(); }
	[[nodiscard]] inline bn::fixed y() const { return candy_sprite.y(); }
	[[nodiscard]] inline bn::fixed rotation() const { return candy_icon_sprite.rotation_angle(); }

	void set_x(bn::fixed v);
	void set_y(bn::fixed v);
	void set_rotation(bn::fixed v);
	void set_scale(bn::fixed v);
	void move_to_top();

	void set_candy_type(int type);
	void set_position(bn::fixed x, bn::fixed y, bn::fixed rotation, bn::fixed scale);
	[[nodiscard]] bool check_press(bn::fixed x, bn::fixed y);

	void set_sprite_palette(const bn::sprite_palette_ptr& palette);

	void randomize_type(bn::random& random, int taken);
	void randomize_position(bn::random& random);
	void randomize_unique_position(bn::random& random, const bn::ivector<candy>& existing_candy);

	void refresh_position_from_index(bn::random& random);

	constexpr static int tiles_width = 10;
	constexpr static int tiles_height = 5;

	bn::sprite_ptr candy_sprite;
	bn::sprite_ptr candy_icon_sprite;

	int position_index;
};

DH_END_NAMESPACE