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
	void update_a_press();

private:
	bn::vector<candy, 25> candy_objects;

	bn::optional<bn::sprite_palette_ptr> unselected_palette;
	bn::optional<bn::sprite_palette_ptr> selected_palette;

	hand cursor;
	candy* hovered_candy = nullptr;
	int candy_type = 0;
};

DH_END_NAMESPACE
