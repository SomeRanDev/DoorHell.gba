#include "dh_hand.h"

#include "bn_keypad.h"

#include "bn_sprite_items_dh_hand.h"

DH_START_NAMESPACE

hand::hand():
	hand_sprite(bn::sprite_items::dh_hand.create_sprite(0, 0))
{
}

void hand::add_x(int x) {
	hand_sprite.set_x(hand_sprite.x() + x);
}

void hand::add_y(int y) {
	hand_sprite.set_y(hand_sprite.y() + y);
}

void hand::update() {
	if(is_actively_pressing()) {
		update_press();
	} else {
		update_normal();
	}
}

void hand::update_normal() {
	if(time++ > 12) {
		time = 0;

		frame = frame == 0 ? 1 : 0;
		set_frame(frame);
	}
}

void hand::update_press() {
	if(time++ > 2) {
		time = 0;

		if(is_pressing == 1) {
			frame++;
			if(frame == 5) {
				is_pressing = 2;
				frame = 3;
			}
		} else {
			frame--;
			if(frame == 1) {
				is_pressing = 0;
			}
		}
	}
	set_frame(frame);
}

void hand::update_movement() {
	int x = 0;
	int y = 0;
	
	if(bn::keypad::left_held()) {
		x = -1;
	} else if(bn::keypad::right_held()) {
		x = 1;
	}

	if(bn::keypad::up_held()) {
		y = -1;
	} else if(bn::keypad::down_held()) {
		y = 1;
	}

	add_x(x);
	add_y(y);
}

void hand::set_frame(int f) {
	hand_sprite.set_tiles(bn::sprite_items::dh_hand.tiles_item(), f);
}

void hand::press() {
	is_pressing = 1;
}

bool hand::is_actively_pressing() const {
	return is_pressing > 0;
}

DH_END_NAMESPACE
