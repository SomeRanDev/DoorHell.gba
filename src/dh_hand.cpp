#include "dh_hand.h"

#include "bn_keypad.h"
#include "bn_math.h"

#include "bn_sprite_items_dh_hand.h"

DH_START_NAMESPACE

constexpr int screen_min_x = (240 / -2);
constexpr int screen_max_x = (240 / 2);
constexpr int screen_min_y = (160 / -2);
constexpr int screen_max_y = (160 / 2);

bn::fixed clamp(bn::fixed value, int min, int max) {
	if(value < min) return min;
	else if(value > max) return max;
	return value;
}

hand::hand():
	hand_sprite(bn::sprite_items::dh_hand.create_sprite(0, 0))
{
}

void hand::add_x(bn::fixed x) {
	hand_sprite.set_x(clamp(hand_sprite.x() + x, screen_min_x, screen_max_x));
}

void hand::add_y(bn::fixed y) {
	hand_sprite.set_y(clamp(hand_sprite.y() + y, screen_min_y, screen_max_y));
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
	bn::fixed x = 0;
	bn::fixed y = 0;
	
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

	if(x != 0 && y != 0) {
		auto sqrt2 = bn::sqrt(bn::fixed(2.0));
		x /= sqrt2;
		y /= sqrt2;
	}

	constexpr bn::fixed speed = 2;

	add_x(x * speed);
	add_y(y * speed);
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
