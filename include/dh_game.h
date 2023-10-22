#pragma once

#include "bn_regular_bg_ptr.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"

#include "mj/mj_game.h"

#include "dh_defines.h"
#include "dh_hand.h"

DH_START_NAMESPACE

enum State {
	Intro,
	Playing
};

class game : public mj::game {
public:
	game(int completed_games, const mj::game_data& data);

	[[nodiscard]]
	bn::string<16> title() const final {
		return "Door Hell";
	}

	[[nodiscard]]
	int total_frames() const final {
		return _total_frames;
	}

	[[nodiscard]]
	bool victory() const final {
		return _victory;
	}

	void fade_in(const mj::game_data& data) final;
	void fade_out(const mj::game_data& data) final;

	[[nodiscard]]
	mj::game_result play(const mj::game_data& data) final;

private:

	void set_current_references(mj::game_result& result, const mj::game_data& data);
	void reset_current_references();

	void set_victory();
	void set_defeat();

	void update();

	void update_intro();
	void update_game();

	// -------------------------------------------
	// STATE
	State state = Intro;

	// -------------------------------------------
	// MICRO GAME
	mj::game_result* current_result = nullptr;
	const mj::game_data* current_data = nullptr;

	// -------------------------------------------
	// INTRO & BACKGROUND
	bn::regular_bg_ptr _bg;

	int intro_time = 0;
	int intro_frame = 0;

	// -------------------------------------------
	// GAME
	hand hand_obj;

	// -------------------------------------------
	// MICRO GAME
	int _total_frames;
	int _show_result_frames = 60;

	bool _victory = false;
	bool _defeat = false;
};

DH_END_NAMESPACE
