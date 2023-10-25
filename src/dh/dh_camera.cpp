#include "dh_camera.h"

#include "bn_sound_items.h"

#include "dh_intro.h"
#include "dh_high_bell.h"
#include "dh_window_bell.h"
#include "dh_right_bell.h"
#include "dh_pumpkin_bell.h"
#include "dh_close_bell.h"
#include "dh_close_left_bell.h"

#include "animations/dh_close_bell_press.h"
#include "animations/dh_close_left_bell_press.h"
#include "animations/dh_right_bell_press.h"
#include "animations/dh_pumpkin_bell_press.h"
#include "animations/dh_high_bell_press.h"
#include "animations/dh_window_bell_press.h"

DH_START_NAMESPACE

namespace {
	constexpr int bg_x = (256 - 240) / 2;
	constexpr int bg_y = (256 - 160) / 2;
}

camera::camera():
	background_bg(background_frames[0]->create_bg(bg_x, bg_y)),
	foreground_bg(frames[0]->create_bg(bg_x, bg_y))
{
}

void camera::set_doorbell_position(int pos) {
	doorbell_position = pos;

	switch(pos) {
		case 0: {
			doorbell_frames = dh_high_bell_frames;
			doorbell_first_index = dh_high_bell_first_index;
			break;
		}
		case 1: {
			doorbell_frames = dh_right_bell_frames;
			doorbell_first_index = dh_right_bell_first_index;
			break;
		}
		case 2: {
			doorbell_frames = dh_close_bell_frames;
			doorbell_first_index = dh_close_bell_first_index;
			break;
		}
		case 3: {
			doorbell_frames = dh_close_left_bell_frames;
			doorbell_first_index = dh_close_left_bell_first_index;
			break;
		}
		case 4: {
			doorbell_frames = dh_pumpkin_bell_frames;
			doorbell_first_index = dh_pumpkin_bell_first_index;
			break;
		}
		case 5: {
			doorbell_frames = dh_window_bell_frames;
			doorbell_first_index = dh_window_bell_first_index;
			break;
		}
		default: {}
	}

	_overlay_bg = doorbell_frames[doorbell_first_index]->create_bg(bg_x, bg_y);
	_overlay_bg->set_visible(false);
}

void camera::set_frame_index(int index) {
		if(_overlay_bg && (animation == nullptr || animation_frame == -1)) {
			if(doorbell_frames[index] == nullptr) {
				_overlay_bg->set_visible(false);
			} else {
				if(current_overlay_bg_index != index) {
					current_overlay_bg_index = index;
					_overlay_bg->set_item(*doorbell_frames[index]);
				}
				_overlay_bg->set_visible(true);
			}
		}

		foreground_bg.set_item(*frames[index]);
		background_bg.set_item(*background_frames[index]);
		//_bg.set_tiles(frames[24]->tiles_item());
		//_bg.set_tiles(*frames[intro_frame]);
}

bool camera::update_intro() {
	if(intro_time++ > 2) {
		intro_time = 0;
		intro_frame++;
		if(intro_frame < intro_frame_count) {
			set_frame_index(intro_frame);
		}
	}
	return intro_frame >= intro_frame_count;
}

bool camera::should_update_hand_intro() const {
	return intro_frame >= 13;
}

bool camera::set_position(int _x, int _y) {
	bool changed = false;

	if(_x >= 0 && _x < world_width) {
		x = _x;
		changed = true;
	}
	if(_y >= 0 && _y < world_height) {
		y = _y;
		changed = true;
	}

	if(changed) {
		refresh_position();
	}

	return changed;
}

void camera::refresh_position() {
	int y_off = y % 4;
	int y_sec = y / 4;
	int index;
	if(y_off == 0) {
		index = ((4 - y_sec - 1) * (world_width + 3)) + x;
	} else {
		index = ((4 - y_sec - 1) * (world_width + 3)) - y_off;
	}
	set_frame_index(game_frame_start + index);
	//_bg.set_item(*frames[game_frame_start + index]);
}

void camera::restrict_movement(int& _x, int& _y) const {
	constexpr int world_width_2 = (world_width / 2);

	if(_x != 0) {
		auto y_off = y % 4;
		if(y_off != 0) {
			_y = y_off <= 1 ? -1 : 1;
			_x = 0;
		}
	}

	auto new_y = y + _y;
	if(_y != 0 && new_y >= 0 && new_y < world_height) {
		if(x > world_width_2) {
			_x = -1;
			_y = 0;
		} else if(x < world_width_2) {
			_x = 1;
			_y = 0;
		}
	}
}

bool camera::shift(int _x, int _y) {
	return set_position(x + _x, y + _y);
}

bool camera::on_a_press() {
	if(_overlay_bg && _overlay_bg->visible()) {
		switch(doorbell_position) {
			case 0: {
				animation = animations::dh_high_bell_press_frames;
				animation_data = animations::dh_high_bell_press_data;
				break;
			}
			case 1: {
				animation = animations::dh_right_bell_press_frames;
				animation_data = animations::dh_right_bell_press_data;
				break;
			}
			case 2: {
				animation = animations::dh_close_bell_press_frames;
				animation_data = animations::dh_close_bell_press_data;
				break;
			}
			case 3: {
				animation = animations::dh_close_left_bell_press_frames;
				animation_data = animations::dh_close_left_bell_press_data;
				break;
			}
			case 4: {
				animation = animations::dh_pumpkin_bell_press_frames;
				animation_data = animations::dh_pumpkin_bell_press_data;
				break;
			}
			case 5: {
				animation = animations::dh_window_bell_press_frames;
				animation_data = animations::dh_window_bell_press_data;
				break;
			}
			default: {}
		}

		// Can only press when on the corrent "Y" position
		if(animation_data[2] != (world_height - y - 1)) {
			animation = nullptr;
			animation_data = nullptr;
			return false;
		}

		animation_frame = -1;
		animation_time = 3;
		return true;
	}
	return false;
}

bool camera::update_animation() {
	if(animation == nullptr) {
		return true;
	}

	if(--animation_time == 0) {
		animation_time = 3;

		// Align "X" before playing animation
		if(x != animation_data[1]) {
			(void)shift(animation_data[1] > x ? 1 : -1, 0);
		} else {
			animation_frame++;

			// Play doorbell sound effect at certain time for some press animations
			if(animation_frame == 5) {
				if(animation == animations::dh_close_bell_press_frames) {
					bn::sound_items::dh_doorbell.play();
				} else if(
					animation == animations::dh_close_left_bell_press_frames ||
					animation == animations::dh_pumpkin_bell_press_frames
				) {
					bn::sound_items::dh_fall.play();
				}
			}

			if(!animation_done() && _overlay_bg) {
				_overlay_bg->set_item(*animation[animation_frame]);
				_overlay_bg->set_visible(true);
			}
		}
	}

	return false;
}

void camera::play_animation_done_sound_effect() {
	if(animation == animations::dh_close_bell_press_frames) {
		bn::sound_items::dh_fall.play();
	} else {
		bn::sound_items::dh_doorbell.play();
	}
}

bool camera::animation_done() {
	return animation_frame >= animation_data[0];
}

DH_END_NAMESPACE
