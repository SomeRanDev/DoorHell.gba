#pragma once

#include "bn_optional.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_vector.h"

#include "mj/mj_game.h"

#include "dh_defines.h"
#include "dh_camera.h"
#include "dh_candy.h"
#include "dh_hand.h"

DH_START_NAMESPACE

/**
 * The implementation for "Door Hell Pt 2".
 * 
 * This contains behavior and fields related to the second micro game.
 */
class impl2 {
public:
	impl2();

	void init(camera& cam, const mj::game_data& data);
	void start_playing(camera& cam, const mj::game_data& data);
	void generate_palettes();
	void generate_candy(const mj::game_data& data);

	void update();
	void update_hovered_candy();
	[[nodiscard]] bool update_a_press();

	void init_candy_display_animation();
	void update_candy_display_animation();

private:
	/**
	 * Stores all the `candy` objects.
	 */
	bn::vector<candy, 20> candy_objects;

	// -------------------------------------------
	// PALETTES
	bn::optional<bn::sprite_palette_ptr> unselected_palette;
	bn::optional<bn::sprite_palette_ptr> selected_palette;

	// -------------------------------------------
	// HAND CURSOR
	hand cursor;
	candy* hovered_candy = nullptr;

	// -------------------------------------------
	// DISPLAY CANDY ANIMATION
	bn::fixed animation_time = 0;
	bn::fixed start_x = 0;
	bn::fixed start_y = 0;
	bn::fixed start_rotation = 0;

	// -------------------------------------------
	// DATA
	int candy_type = 0;

	bool is_displaying_candy = false;
};

DH_END_NAMESPACE