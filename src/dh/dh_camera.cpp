#include "dh/dh_camera.h"

#include "dh/dh_intro.h"
#include "dh/dh_high_bell.h"
#include "dh/dh_close_bell.h"

DH_START_NAMESPACE

#define overlay_frames dh_close_bell_frames
#define overlay_first dh_close_bell_first_index

constexpr int bg_x = (256 - 240) / 2;
constexpr int bg_y = (256 - 160) / 2;

camera::camera():
	_bg(frames[0]->create_bg(bg_x, bg_y)),
	_overlay_bg(overlay_frames[overlay_first]->create_bg(bg_x, bg_y))
{
	_overlay_bg.set_visible(false);
}

void camera::set_frame_index(int index) {
		if(overlay_frames[index] == nullptr) {
			_overlay_bg.set_visible(false);
		} else {
			_overlay_bg.set_visible(true);
			BN_LOG(index);
			_overlay_bg.set_item(*overlay_frames[index]);
		}

		_bg.set_item(*frames[index]);
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

bool camera::shift(int _x, int _y) {
	constexpr int world_width_2 = (world_width / 2);

	if(_x != 0) {
		auto y_off = y % 4;
		if(y_off != 0) {
			_y = y_off <= 1 ? -1 : 1;
			_x = 0;
		}
	}

	if(_y != 0) {
		if(x > world_width_2) {
			_x = -1;
			_y = 0;
		} else if(x < world_width_2) {
			_x = 1;
			_y = 0;
		}
	}
	
	return set_position(x + _x, y + _y);
}

DH_END_NAMESPACE
