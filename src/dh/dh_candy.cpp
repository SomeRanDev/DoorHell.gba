#include "dh_candy.h"

#include "bn_math.h"
#include "bn_math.h"

#include "bn_sprite_items_dh_candy.h"
#include "bn_sprite_items_dh_candy_icon.h"

DH_START_NAMESPACE

candy::candy():
	candy_sprite(bn::sprite_items::dh_candy.create_sprite(0, 0)),
	candy_icon_sprite(bn::sprite_items::dh_candy_icon.create_sprite(0, 0))
{
	candy_icon_sprite.set_scale(2);
}

void candy::set_candy_type(int type) {
	candy_icon_sprite.set_tiles(bn::sprite_items::dh_candy_icon.tiles_item(), type);
}

void candy::set_position(bn::fixed x, bn::fixed y, bn::fixed rotation, bn::fixed scale) {
	DH_UNUSED(scale);

	// ---------
	// Wrapper
	candy_sprite.set_x(x);
	candy_sprite.set_y(y);
	candy_sprite.set_tiles(bn::sprite_items::dh_candy.tiles_item(), ((rotation / 180.0) * 9.0).floor_integer() % 9);
	// candy_sprite.set_scale(scale);

	// ---------
	// Icon
	candy_icon_sprite.set_x(x);
	candy_icon_sprite.set_y(y);
	candy_icon_sprite.set_rotation_angle(rotation);
	// candy_icon_sprite.set_scale(scale * 2.0);
}

bool candy::check_press(bn::fixed test_x, bn::fixed test_y) {
	// Radius of the candy hitbox
	constexpr int size = 20;

	bn::fixed xo = test_x - candy_sprite.x() + (size / 2);
	if(xo > size || xo < -size) return false;

	bn::fixed yo = test_y - candy_sprite.y() + (size / 2);
	if(yo > size || yo < -size) return false;

	return bn::sqrt(xo * xo + yo * yo) < size;
}

void candy::set_sprite_palette(const bn::sprite_palette_ptr& palette) {
	candy_sprite.set_palette(palette);
}

void candy::randomize_type(bn::random& random, int taken) {
	int type;
	do {
		type = random.get_int(11);
	} while(type == taken);

	set_candy_type(type);
}

void candy::randomize_position(bn::random& random) {
	position_index = random.get_int(tiles_width * tiles_height);
	refresh_position_from_index(random);

	// Hardcoded approximate boundaries of the "candy bag" background.
	// set_position(random.get_int(-100, 66), random.get_int(-12, 66), random.get_int(360), random.get_fixed(0.5) + 0.5);
}

void candy::randomize_unique_position(bn::random& random, const bn::ivector<candy>& existing_candy) {
	// Allow overlaps every 10 pieces added...
	//int overlaps_allowed = existing_candy.size() / 7;

	while(true) {
		randomize_position(random);

		bool overlaps = false;

		int start = bn::max(0, existing_candy.size() - 5);
		int end = existing_candy.size();
		for(int i = start; i < end; i++) {
			const candy& c = existing_candy[i];
			if(
				bn::abs(c.position_index - position_index) <= 2 ||
				(c.position_index - tiles_width) == position_index ||
				(c.position_index + tiles_width) == position_index
			) {
				overlaps = true;
				break;
			}
		}

		if(!overlaps) {
			break;
		}
	}
}

void candy::refresh_position_from_index(bn::random& random) {
	set_position(
		((position_index % tiles_width) * 16) - 100,
		((position_index / tiles_width) * 16) - 12,
		random.get_int(360),
		random.get_fixed(0.5) + 0.5
	);
}

DH_END_NAMESPACE
