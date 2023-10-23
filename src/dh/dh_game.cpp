#include "dh/dh_game.h"

#include "bn_keypad.h"

#include "dh/dh_intro.h"

DH_START_NAMESPACE

game::game(int completed_games, const mj::game_data& data):
	_total_frames(maximum_frames)
{
	(void)play_jingle(mj::game_jingle_type::METRONOME_16BEAT, completed_games, data);

	hand_obj.start_intro();
}

void game::init(const mj::game_data& data) {
	cam.set_doorbell_position(data.random.get_int(3));
}

void game::fade_in([[maybe_unused]] const mj::game_data& data) {
	update_intro();
}

void game::fade_out([[maybe_unused]] const mj::game_data& data) {
}

mj::game_result game::play(const mj::game_data& data) {
	if(!_initialized) {
		_initialized = true;
		init(data);
	}

	mj::game_result result;
	result.exit = data.pending_frames == 0;

	if(!_victory && !_defeat) {
		set_current_references(result, data);
		update();
		reset_current_references();
	} else {
		if(_show_result_frames) {
			_show_result_frames--;
		} else {
			result.exit = true;
		}
	}

	return result;
}

void game::set_current_references(mj::game_result& result, const mj::game_data& data) {
	current_result = &result;
	current_data = &data;
}

void game::reset_current_references() {
	current_result = nullptr;
	current_data = nullptr;
}

void game::set_victory() {
	if(current_result) {
		current_result->remove_title = true;
	}
	_victory = true;
}

void game::set_defeat() {
	if(current_result) {
		current_result->remove_title = true;
	}
	_defeat = true;
}

void game::update() {
	if(state == Intro) {
		update_intro();
	} else {
		update_game();
	}
}

void game::update_intro() {
	if(cam.update_intro()) {
		state = Playing;
	}
	if(cam.should_update_hand_intro()) {
		//hand_obj.update_intro();
	}
}

void game::update_game() {
	// if(!hand_obj.is_actively_pressing()) {
	// 	hand_obj.update_movement();
	// 	if(bn::keypad::a_pressed()) {
	// 		hand_obj.press();
	// 	}
	// }

	// hand_obj.update();

	if(cam.update_animation()) {
		update_movement();
	} else if(!_victory && cam.animation_done()) {
		// TODO play door bell
		set_victory();
	}

	//hand_obj.set_tiles(bn::sprite_items::dh_hand.tiles_item(), 4);

	// if(bn::keypad::a_pressed()) {
	// 	_bg.set_item(bn::regular_bg_items::tmg_you_win);
	// 	set_victory();
	// }
	// else if(!bn::keypad::start_pressed() && bn::keypad::any_pressed()) {
	// 	_bg.set_item(bn::regular_bg_items::tmg_you_lose);
	// 	set_defeat();
	// }
}

void game::update_movement() {
	if(bn::keypad::a_pressed()) {
		if(cam.on_a_press()) {
			return;
		}
	}

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

	cam.restrict_movement(x, y);

	static int last_move_type = -1;
	int move_type = (y * 3) + x;

	if(last_move_type == move_type && camera_move_cooldown > 0) {
		camera_move_cooldown--;
	} else if(cam.shift(x, y)) {
		last_move_type = move_type;
		camera_move_cooldown = 2;
	}
}

DH_END_NAMESPACE
