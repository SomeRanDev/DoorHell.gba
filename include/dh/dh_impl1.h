#pragma once

// #include "bn_optional.h"
// #include "bn_sprite_palette_ptr.h"
// #include "bn_vector.h"

// #include "mj/mj_game.h"

#include "dh_defines.h"
#include "dh_camera.h"
// #include "dh_candy.h"
// #include "dh_hand.h"

DH_START_NAMESPACE

/**
 * The implementation for "Door Hell" (the part 1 version).
 * 
 * This contains behavior and fields related to the first micro game.
 */
class impl1 {
public:
	impl1();

	[[nodiscard]] bool update(camera& cam, bool is_victory);
	void update_movement(camera& cam);

	// void init(camera& cam, const mj::game_data& data);
	// void start_playing(camera& cam, const mj::game_data& data);
	// void generate_palettes();
	// void generate_candy(const mj::game_data& data);

	// void update();
	// void update_hovered_candy();
	// void update_a_press();

private:
	int sleep = 0;

	int camera_move_cooldown = 0;

	// bn::vector<candy, 25> candy_objects;

	// bn::optional<bn::sprite_palette_ptr> unselected_palette;
	// bn::optional<bn::sprite_palette_ptr> selected_palette;

	// hand cursor;
	// candy* hovered_candy = nullptr;
	// int candy_type = 0;
};

DH_END_NAMESPACE
