#include "dh_game.h"

#include "bn_keypad.h"
#include "bn_math.h"

#include "bn_sound_items.h"

DH_START_NAMESPACE

// ========================================================================
// * base_game
// ========================================================================

base_game::base_game(const char* name, int _completed_games, const mj::game_data& data, bool is_part_2):
	mj::game(name),
	cam(is_part_2),
	level(recommended_difficulty_level(completed_games, data)),
	completed_games(_completed_games)
{}

void base_game::generate_tutorial_text(const char* msg, const mj::game_data& data) {
	// Show tutorial text
	auto x = 260;
	data.small_text_generator.generate(x, 5, msg, text_sprites);

	// Record text offsets
	auto mid = data.small_text_generator.width(msg) / -2;
	DH_FOR(text_sprites.size()) {
		text_sprites[i].set_bg_priority(1); // show text above backgrounds
		text_offsets.push_back(text_sprites[i].x() - x + mid);
	}
}

void base_game::on_first_update([[maybe_unused]] const mj::game_data& data) {
}

void base_game::fade_in([[maybe_unused]] const mj::game_data& data) {
	update_intro();
	update_text();
}

void base_game::fade_out([[maybe_unused]] const mj::game_data& data) {
}

mj::game_result base_game::play(const mj::game_data& data) {
	if(!is_initialized) {
		is_initialized = true;
		on_first_update(data);
	}

	mj::game_result result;
	result.exit = data.pending_frames == 0;

	if(!is_victory && !is_defeat) {
		set_current_references(result, data);
		update();
		reset_current_references();
	} else {
		update_exit(result);
	}

	return result;
}

void base_game::update_exit(mj::game_result& result) {
	if(show_result_frames == -1) {
		update_exit_preresult();
	} else if(show_result_frames) {
		show_result_frames--;
	} else {
		result.exit = true;
	}
}

void base_game::set_current_references(mj::game_result& result, const mj::game_data& data) {
	current_result = &result;
	current_data = &data;
}

void base_game::reset_current_references() {
	current_result = nullptr;
	current_data = nullptr;
}

void base_game::set_victory() {
	if(current_result) {
		current_result->remove_title = true;
	}
	is_victory = true;
}

void base_game::set_defeat() {
	if(current_result) {
		current_result->remove_title = true;
	}
	is_defeat = true;
}

void base_game::start_playing() {
	state = Playing;
	on_start_playing();
}

void base_game::on_start_playing() {
	// Possibly implemented in child classes...
}

void base_game::update() {
	if(state == Intro) {
		update_intro();
	} else {
		update_game();
	}

	update_text();
}

void base_game::update_intro() {
	if(cam.update_intro()) {
		start_playing();
	}
}

void base_game::update_text() {
	if(text_offsets.size() > 0 && text_ratio < 1.0) {
		bool is_middle = text_ratio > 0.42 && text_ratio < 0.58;
		text_ratio += is_middle ? 0.003 : 0.05;

		DH_FOR(text_sprites.size()) {
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

// ========================================================================
// * game1
// ========================================================================

game1::game1(int _completed_games, const mj::game_data& data):
	base_game("dh", _completed_games, data, false)
{
	total_frames_value = play_bgm(data);
	generate_tutorial_text("Ring the doorbell.", data);
	part_1.setup_palette(cam, data);
}

int game1::play_bgm(const mj::game_data& data) {
	auto jingle = (
		completed_games >= 24 ? mj::game_jingle_type::TOTSNUK05 : mj::game_jingle_type::TOTSNUK06
	);
	return play_jingle(jingle, completed_games, data);
}

void game1::on_first_update(const mj::game_data& data) {
	part_1.on_first_update(cam, level, data);
}

void game1::update_exit_preresult() {
	show_result_frames = 45;
}

void game1::update_game() {
	if(part_1.update(cam, is_victory)) {
		set_victory();
	}
}

void game1::on_pause_start([[maybe_unused]] const mj::game_data& data) {
	part_1.on_pause_start(cam);
	controls_sprite.emplace(false, current_data->small_text_generator);
}

void game1::on_pause_end([[maybe_unused]] const mj::game_data& data) {
	part_1.on_pause_end(cam);
	controls_sprite.reset();
}

// ========================================================================
// * game2
// ========================================================================

game2::game2(int _completed_games, const mj::game_data& data):
	base_game("dh2", _completed_games, data, true)
{
	total_frames_value = play_bgm(data);
	part_2.init(cam, data);
}

int game2::play_bgm(const mj::game_data& data) {
	auto jingle = mj::game_jingle_type::TOTSNUK16;
	return play_jingle(jingle, completed_games, data);
}

void game2::update_exit_preresult() {
	if(part_2.update() == 3) {
		show_result_frames = 15;
	}
	update_text();
}

void game2::on_start_playing() {
	generate_tutorial_text("Pick your favorite.", *current_data);
	part_2.start_playing(cam, level, completed_games, *current_data);
	controls_sprite.emplace(true, current_data->small_text_generator);
}

void game2::fade_out([[maybe_unused]] const mj::game_data& data) {
	update();
}

void game2::update_game() {
	switch(part_2.update()) {
		case 1: {
			set_victory();
			break;
		}
		case 2: {
			set_defeat();
			break;
		}
		default: {}
	}
}

void game2::on_pause_start([[maybe_unused]] const mj::game_data& data) {
	part_2.on_pause_start();
}

void game2::on_pause_end([[maybe_unused]] const mj::game_data& data) {
	part_2.on_pause_end();
}

DH_END_NAMESPACE
