#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed.h"
#include "bn_vector.h"

#include "mj/mj_game.h"

#include "dh_defines.h"
#include "dh_camera.h"

DH_START_NAMESPACE

enum State {
	Intro,
	Playing
};

class game : public mj::game {
public:
	game(int completed_games, const mj::game_data& data);

	[[nodiscard]]
	bool check_if_part_2() const {
		return progress % 2 == 1;
	}

	[[nodiscard]]
	bn::string<16> title() const final {
		//if(is_part_2()) {
			return "Door Hell (Pt 2)";
		//}
		return "Door Hell";
	}

	[[nodiscard]]
	int total_frames() const final {
		return total_frames_value;
	}

	[[nodiscard]]
	bool victory() const final {
		return is_victory;
	}

	void fade_in(const mj::game_data& data) final;
	void fade_out(const mj::game_data& data) final;

	[[nodiscard]]
	mj::game_result play(const mj::game_data& data) final;

private:
	// -------------------------------------------
	// STATICS
	static int progress;

	// -------------------------------------------
	// FUNCTIONS
	int play_bgm(int completed_games, const mj::game_data& data);
	void generate_tutorial_text(const mj::game_data& data);
	void setup_palette(int completed_games);

	void init(const mj::game_data& data);
	int generate_unique_random_position(const mj::game_data& data) const;

	void set_current_references(mj::game_result& result, const mj::game_data& data);
	void reset_current_references();

	void set_victory();
	void set_defeat();

	void update();

	void update_intro();
	void update_text();
	void update_game();
	void update_movement();

	void update_game_part_2();

	// -------------------------------------------
	// TEXT SPRITES
	bn::vector<bn::sprite_ptr, 5> text_sprites;
	bn::vector<bn::fixed, 5> text_offsets;
	bn::fixed text_ratio;

	// -------------------------------------------
	// STATE
	State state = Intro;

	// -------------------------------------------
	// MICRO GAME
	mj::game_result* current_result = nullptr;
	const mj::game_data* current_data = nullptr;

	// -------------------------------------------
	// CAMERA
	camera cam;
	int camera_move_cooldown = 0;

	// -------------------------------------------
	// MICRO GAME
	int sleep = 0;

	int total_frames_value;
	int show_result_frames = 60;

	bool is_victory = false;
	bool is_defeat = false;

	bool is_initialized = false;
	bool is_part_2 = false;
};

DH_END_NAMESPACE
