#pragma once

#include "bn_fixed.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

#include "mj/mj_game.h"
#include "mj/mj_difficulty_level.h"

#include "dh_defines.h"
#include "dh_camera.h"
#include "dh_candy.h"
#include "dh_controls.h"
#include "dh_hand.h"
#include "dh_impl1.h"
#include "dh_impl2.h"

DH_START_NAMESPACE

enum State {
	Intro,
	Playing
};

/**
 * The base class for the implementation for both parts of "Door Hell".
 */
class base_game : public mj::game {
public:
	base_game(int _completed_games, const mj::game_data& data, bool is_part_2):
		cam(is_part_2),
		level(recommended_difficulty_level(completed_games, data)),
		completed_games(_completed_games)
	{}

	[[nodiscard]]
	int total_frames() const final {
		return total_frames_value;
	}

	[[nodiscard]]
	bool victory() const final {
		return is_victory;
	}

	void fade_in(const mj::game_data& data) final;
	void fade_out(const mj::game_data& data);

	[[nodiscard]]
	mj::game_result play(const mj::game_data& data) final;

protected:
	// -------------------------------------------
	// UNIMPLEMENTED
	virtual int play_bgm(const mj::game_data& data) = 0;
	virtual void update_exit_preresult() = 0;
	virtual void update_game() = 0;

	// -------------------------------------------
	// VIRTUAL
	virtual void on_first_update(const mj::game_data& data);
	virtual void on_start_playing();

	// -------------------------------------------
	// FUNCTIONS
	void generate_tutorial_text(const char* msg, const mj::game_data& data);
	void update_exit(mj::game_result& result);

	int generate_unique_random_position(const mj::game_data& data) const;

	void set_current_references(mj::game_result& result, const mj::game_data& data);
	void reset_current_references();

	void set_victory();
	void set_defeat();

	void start_playing();
	void generate_candy();

	void update();
	void update_intro();
	void update_text();

	// -------------------------------------------
	// TEXT SPRITES
	bn::vector<bn::sprite_ptr, 5> text_sprites;
	bn::vector<bn::fixed, 5> text_offsets;
	bn::fixed text_ratio = -0.5; // Set to negative number to delay appearance

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

	// -------------------------------------------
	// CONTROLS
	bn::optional<controls> controls_sprite;

	// -------------------------------------------
	// MICRO GAME
	mj::difficulty_level level;
	int completed_games;

	int total_frames_value;
	int show_result_frames = -1;

	bool is_victory = false;
	bool is_defeat = false;

	bool is_initialized = false;
};

/**
 * Part 1 of "Door Hell" (Ring the doorbell.)
 */
class game1 : public base_game {
public:
	game1(int _completed_games, const mj::game_data& data);

	[[nodiscard]]
	bn::string<16> title() const final {
		return "Door Hell";
	}

	int play_bgm(const mj::game_data& data);

	void on_first_update(const mj::game_data& data) final;
	void update_exit_preresult() final;
	void update_game() final;

	void on_pause_start(const mj::game_data& data) final;
	void on_pause_end(const mj::game_data& data) final;

private:
	/**
	 * The implementation and behavior for the "part 1" version.
	 */
	impl1 part_1;
};

/**
 * Part 2 of "Door Hell" (Pick your favorite candy.)
 */
class game2 : public base_game {
public:
	game2(int _completed_games, const mj::game_data& data);

	[[nodiscard]]
	bn::string<16> title() const final {
		return "Door Hell 2";
	}

	int play_bgm(const mj::game_data& data);

	void update_exit_preresult() final;
	void on_start_playing() final;

	void fade_out(const mj::game_data& data) final;
	void update_game() final;

	void on_pause_start(const mj::game_data& data) final;
	void on_pause_end(const mj::game_data& data) final;

private:
	/**
	 * The implementation and behavior for the "part 2" version.
	 */
	impl2 part_2;
};

DH_END_NAMESPACE
