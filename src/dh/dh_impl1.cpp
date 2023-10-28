#include "dh_impl1.h"

#include "bn_keypad.h"
#include "bn_sound_items.h"

DH_START_NAMESPACE

impl1::impl1() {
}

bool impl1::update(camera& cam, bool is_victory) {
	if(sleep > 0) {
		sleep--;
	} else if(cam.update_animation()) {
		update_movement(cam);
	} else if(!is_victory && cam.animation_done()) {
		cam.play_animation_done_sound_effect();
		return true;
	}
	return false;
}

void impl1::update_movement(camera& cam) {
	if(bn::keypad::a_pressed()) {
		if(cam.on_a_press()) {
			return;
		} else {
			bn::sound_items::dh_denied.play();
			sleep = 16;
			return;
		}
	}

	int x = 0;
	int y = 0;
	
	if(bn::keypad::left_held()) {
		x = -1;
	} else if(bn::keypad::right_held()) {
		x = 1;
	} else if(bn::keypad::up_held()) {
		y = -1;
	} else if(bn::keypad::down_held()) {
		y = 1;
	}

	cam.restrict_movement(x, y);

	static int last_move_type = -1;
	int move_type = (y * 3) + x;

	if(camera_move_cooldown > 0) {
		if(last_move_type != move_type) {
			camera_move_cooldown = 0;
		} else {
			camera_move_cooldown--;
		}
	} else if(cam.shift(x, y)) {
		last_move_type = move_type;
		camera_move_cooldown = 2;
	}
}

DH_END_NAMESPACE
