#include "dh_impl1.h"

#include "bn_keypad.h"
#include "bn_sound_items.h"

DH_START_NAMESPACE

impl1::impl1() {
}

void impl1::setup_palette(camera& cam, int completed_games, int progress) {
	DH_UNUSED(completed_games);
	if(progress == 2) {
		cam.set_palette_type(1);
	} else if(progress == 4) {
		cam.set_palette_type(2);
		progress = 0;
	}
}

void impl1::on_first_update(camera& cam, const mj::game_data& data) {
	cam.set_doorbell_position(generate_unique_random_position(data));
}

int impl1::generate_unique_random_position(const mj::game_data& data) const {
	// Ensure previous four positions not used
	static int previous = 0;

	// There's probably better way to do this... but... uh.... it's a game jam game bro gimme a break lmao
	int position;
	do {
		position = data.random.get_int(6) + 1; // Add one so zero doesn't count
	} while(
		position == (previous & 0xf) ||
		position == ((previous >> 4) & 0xf) ||
		position == ((previous >> 8) & 0xf) ||
		position == ((previous >> 12) & 0xf)
	);

	// Add result to "previous" variable
	previous <<= 4;
	previous |= position;

	return position - 1; // Remove one since positions start from zero
}

bool impl1::update(camera& cam, bool is_victory) {
	if(sleep > 0) {
		sleep--;
	} else if(cam.update_animation()) {
		update_controls(cam);
	} else if(!is_victory && cam.animation_done()) {
		cam.play_animation_done_sound_effect();
		return true;
	}
	return false;
}

void impl1::update_controls(camera& cam) {
	update_a_pressed(cam);
	update_movement(cam);
}

void impl1::update_movement(camera& cam) {
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

void impl1::update_a_pressed(camera& cam) {
	if(bn::keypad::a_pressed()) {
		if(cam.on_a_press()) {
			return;
		} else {
			bn::sound_items::dh_denied.play();
			sleep = 16;
			return;
		}
	}
}

DH_END_NAMESPACE
