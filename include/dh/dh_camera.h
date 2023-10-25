#pragma once

#include "bn_regular_bg_ptr.h"
#include "bn_optional.h"

#include "dh_defines.h"

DH_START_NAMESPACE

class camera {
public:
	camera();

	void set_doorbell_position(int pos);

	void set_frame_index(int index);

	[[nodiscard]] bool update_intro();
	[[nodiscard]] bool should_update_hand_intro() const;

	[[nodiscard]] bool set_position(int _x, int _y);
	void refresh_position();

	void restrict_movement(int& _x, int& _y) const;
	[[nodiscard]] bool shift(int _x, int _y);

	[[nodiscard]] bool on_a_press();
	[[nodiscard]] bool update_animation();
	[[nodiscard]] bool animation_done();

	void play_animation_done_sound_effect();

	static constexpr int world_width = 11;
	static constexpr int world_height = 13;

private:
	bn::regular_bg_ptr background_bg;
	bn::regular_bg_ptr foreground_bg;
	bn::optional<bn::regular_bg_ptr> _overlay_bg;

	const bn::regular_bg_item* const* doorbell_frames;
	int doorbell_first_index = 0;
	int doorbell_position = 0;

	int current_overlay_bg_index = -1;

	int x = 3;
	int y = 13;

	int intro_time = 0;
	int intro_frame = 0;

	const bn::regular_bg_item* const* animation = nullptr;
	int const* animation_data = nullptr;
	int animation_frame = 0;
	int animation_time = 0;
};

DH_END_NAMESPACE
