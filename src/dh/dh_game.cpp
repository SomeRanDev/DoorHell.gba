#include "dh/dh_game.h"

#include "bn_keypad.h"
#include "bn_math.h"

#include "dh/dh_intro.h"

#include "bn_sound_items.h"

DH_START_NAMESPACE

game::game(int completed_games, const mj::game_data& data):
	text_ratio(-0.5), // set to negative number to delay appearance
	_total_frames(
		play_jingle(
			completed_games >= 8 ? mj::game_jingle_type::TOTSNUK05 : mj::game_jingle_type::TOTSNUK06,
			completed_games,
			data
		)
	)
{
	hand_obj.start_intro();

	// Show tutorial text
	auto msg = "Ring the doorbell.";
	auto x = 260;
    data.small_text_generator.generate(x, 5, msg, text_sprites);

	// Record text offsets
	auto mid = data.small_text_generator.width(msg) / -2;
	auto len = text_sprites.size();
	for(decltype(len) i = 0; i < len; i++) {
		text_offsets.push_back(text_sprites[i].x() - x + mid);
	}
}

void game::init(const mj::game_data& data) {
	// Ensure previous two positions not used
	static int previous[] = {-1, -1};

	int position;
	do {
		position = data.random.get_int(6);
	} while(position == previous[0] || position == previous[1]);

	previous[0] = previous[1];
	previous[1] = position;

	cam.set_doorbell_position(position);
}

void game::fade_in([[maybe_unused]] const mj::game_data& data) {
	update_intro();
	update_text();
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

	update_text();
}

void game::update_intro() {
	if(cam.update_intro()) {
		state = Playing;
	}
	if(cam.should_update_hand_intro()) {
		//hand_obj.update_intro();
	}
}

void game::update_text() {
	if(text_ratio < 1.0) {
		bool is_middle = text_ratio > 0.42 && text_ratio < 0.58;
		text_ratio += is_middle ? 0.003 : 0.05;

		auto len = text_sprites.size();
		for(decltype(len) i = 0; i < len; i++) {
			if(is_middle) {
				text_sprites[i].set_x(text_sprites[i].x() + 1);
			} else {
				text_sprites[i].set_x(text_offsets[i] + (260.0 * text_ratio) - (240.0 / 2.0));
			}
		}

		if(text_ratio >= 1.0) {
			text_sprites.clear();
		}
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

	if(_sleep > 0) {
		_sleep--;
	} else if(cam.update_animation()) {
		update_movement();
	} else if(!_victory && cam.animation_done()) {
		cam.play_animation_done_sound_effect();
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
		} else {
			bn::sound_items::dh_denied.play();
			_sleep = 16;
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
