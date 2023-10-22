#include "dh/dh_camera.h"

#include "dh/dh_intro.h"

DH_START_NAMESPACE

camera::camera():
	_bg(frames[0]->create_bg((256 - 240) / 2, (256 - 160) / 2))
{
}

bool camera::update_intro() {
	if(intro_time++ > 2) {
		intro_time = 0;
		intro_frame++;
		if(intro_frame < intro_frame_count) {
			_bg.set_item(*frames[intro_frame]);
			//_bg.set_tiles(frames[24]->tiles_item());
			//_bg.set_tiles(*frames[intro_frame]);
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
	int index = ((world_height - y - 1) * world_width) + x;
	BN_LOG(x, ", ", y, ", ", index);
	_bg.set_item(*frames[game_frame_start + index]);
}

bool camera::shift(int _x, int _y) {
	return set_position(x + _x, y + _y);
}

DH_END_NAMESPACE
