#include "dh_game.h"

#include "bn_keypad.h"
#include "bn_math.h"

#include "bn_sound_items.h"

DH_START_NAMESPACE

int game::progress = 0;

game::game(int completed_games, const mj::game_data& data):
	text_ratio(-0.5), // set to negative number to delay appearance
	cam(check_if_part_2()),
	is_part_2(check_if_part_2())
{
	total_frames_value = play_bgm(completed_games, data);

	if(is_part_2) {
		part_2.init(cam, data);
	} else {
		generate_tutorial_text("Ring the doorbell.", data);
		setup_palette(completed_games);
	}
}

int game::play_bgm(int completed_games, const mj::game_data& data) {
	auto jingle = is_part_2 ? mj::game_jingle_type::TOTSNUK16 : (
		completed_games >= 8 ? mj::game_jingle_type::TOTSNUK05 : mj::game_jingle_type::TOTSNUK06
	);
	return play_jingle(jingle, completed_games, data);
}

void game::generate_tutorial_text(const char* msg, const mj::game_data& data) {
	// Show tutorial text
	//auto msg = "Ring the doorbell.";
	auto x = 260;
	data.small_text_generator.generate(x, 5, msg, text_sprites);

	// Record text offsets
	auto mid = data.small_text_generator.width(msg) / -2;
	DH_FOR(text_sprites.size()) {
		text_sprites[i].set_bg_priority(1); // show text above backgrounds
		text_offsets.push_back(text_sprites[i].x() - x + mid);
	}
}

void game::setup_palette(int completed_games) {
	DH_UNUSED(completed_games);
	if(progress == 2) {
		cam.set_palette_type(1);
	} else if(progress == 4) {
		cam.set_palette_type(2);
		progress = 0;
	}
}

void game::init(const mj::game_data& data) {
	cam.set_doorbell_position(generate_unique_random_position(data));
}

int game::generate_unique_random_position(const mj::game_data& data) const {
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

void game::fade_in([[maybe_unused]] const mj::game_data& data) {
	update_intro();
	update_text();
}

void game::fade_out([[maybe_unused]] const mj::game_data& data) {
}

mj::game_result game::play(const mj::game_data& data) {
	if(!is_initialized) {
		is_initialized = true;
		init(data);
	}

	mj::game_result result;
	result.exit = data.pending_frames == 0;

	if(!is_victory && !is_defeat) {
		set_current_references(result, data);
		update();
		reset_current_references();
	} else {
		if(show_result_frames) {
			show_result_frames--;
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
	is_victory = true;
	progress++;
}

void game::set_defeat() {
	if(current_result) {
		current_result->remove_title = true;
	}
	is_defeat = true;
}

void game::start_playing() {
	state = Playing;

	if(is_part_2) {
		generate_tutorial_text("Pick your favorite.", *current_data);
		part_2.start_playing(cam, *current_data);
	}
}

void game::update() {
	if(state == Intro) {
		update_intro();
	} else if(is_part_2) {
		part_2.update();
	} else {
		if(part_1.update(cam, is_victory)) {
			set_victory();
		}
	}

	update_text();
}

void game::update_intro() {
	if(cam.update_intro()) {
		start_playing();
	}
}

void game::update_text() {
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

DH_END_NAMESPACE
