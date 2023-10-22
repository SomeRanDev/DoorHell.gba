#include "dh_game.h"

#include "bn_keypad.h"

#include "dh_intro.h"

#include "bn_log.h"

DH_START_NAMESPACE

game::game(int completed_games, const mj::game_data& data):
	_bg(intro_frames[0]->create_bg((256 - 240) / 2, (256 - 160) / 2)),
	_total_frames(maximum_frames)
{
	(void)play_jingle(mj::game_jingle_type::METRONOME_16BEAT, completed_games, data);
}

void game::fade_in([[maybe_unused]] const mj::game_data& data) {
	update_intro();
}

void game::fade_out([[maybe_unused]] const mj::game_data& data) {
}

mj::game_result game::play(const mj::game_data& data) {
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
	if(intro_time++ > 4) {
		intro_time = 0;
		intro_frame++;
		if(intro_frame >= intro_frame_count) {
			state = Playing;
		} else {
			_bg.set_item(*intro_frames[intro_frame]);
			//_bg.set_tiles(intro_frames[24]->tiles_item());
		}
	}
}

void game::update_game() {
	if(!hand_obj.is_actively_pressing()) {
		hand_obj.update_movement();
		if(bn::keypad::a_pressed()) {
			hand_obj.press();
		}
	}

	hand_obj.update();

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

DH_END_NAMESPACE
