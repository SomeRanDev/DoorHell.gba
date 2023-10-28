#include "dh_impl2.h"

#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_sprite_palette_item.h"

DH_START_NAMESPACE

impl2::impl2() {
}

void impl2::init(camera& cam, const mj::game_data& data) {
	candy_type = data.random.get_int(12);
	cam.set_candy_type(candy_type);
}

void impl2::start_playing(camera& cam, const mj::game_data& data) {
	// Setup camera
	cam.clear_backgrounds();
	cam.start_part_2();

	// Setup candy
	generate_palettes();
	generate_candy(data);

	// Setup hand
	cursor.start_intro();
}

void impl2::generate_palettes() {
	#define b bn::color(0, 0, 0)

	constexpr bn::color unselected_palette_colors[] = {
		b, b, b, bn::color(31, 31, 31), b, b, b, b, b, b, b, b, b, b, b, b
	};
	constexpr bn::color selected_palette_colors[] = {
		b, bn::color(31, 26, 0), b, bn::color(31, 31, 31), b, b, b, b, b, b, b, b, b, b, b, b
	};

	#undef b

	unselected_palette = bn::sprite_palette_item(unselected_palette_colors, bn::bpp_mode::BPP_4).create_palette();
	selected_palette = bn::sprite_palette_item(selected_palette_colors, bn::bpp_mode::BPP_4).create_palette();
}

void impl2::generate_candy(const mj::game_data& data) {
	bn::random& random = data.random;

	{
		auto c = candy_objects.emplace_back();
		c.set_candy_type(candy_type);
		c.randomize_position(random);
	}

	// auto len = random.get_int(20) + 4;
	DH_FOR(12) {
		candy c;
		c.randomize_type(random, candy_type);
		c.randomize_unique_position(random, candy_objects);
		candy_objects.push_back(bn::move(c));
	}
}

void impl2::update() {
	if(is_displaying_candy) {
		update_candy_display_animation();
	} else {
		update_hovered_candy();
		if(update_a_press()) {
			init_candy_display_animation();
			cursor.set_visible(false);
		} else {
			cursor.update();
		}
	}
}

void impl2::update_hovered_candy() {
	auto hand_x = cursor.x();
	auto hand_y = cursor.y();
	candy* new_hovered_candy = nullptr;
	for(auto i = candy_objects.rbegin(); i != candy_objects.rend(); i++) {
		if((*i).check_press(hand_x, hand_y)) {
			new_hovered_candy = &(*i);
			break;
		}
	}

	if(hovered_candy != new_hovered_candy) {
		if(hovered_candy != nullptr) {
			hovered_candy->set_sprite_palette(unselected_palette.value());
		}
		if(new_hovered_candy != nullptr) {
			new_hovered_candy->set_sprite_palette(selected_palette.value());
		}
		hovered_candy = new_hovered_candy;
	}
}

bool impl2::update_a_press() {
	if(!cursor.is_actively_pressing()) {
		cursor.update_movement();
		if(bn::keypad::a_pressed()) {
			cursor.press();
			if(hovered_candy != nullptr) {
				return true;
			}
		}
	}
	return false;
}

void impl2::init_candy_display_animation() {
	is_displaying_candy = true;

	hovered_candy->move_to_top();

	animation_time = 0;
	start_x = hovered_candy->x();
	start_y = hovered_candy->y();
	start_rotation = hovered_candy->rotation();

	// If it's not going to spin that much, let's make it SPINNNNNN
	if(start_rotation < 180) start_rotation += 360;
}

void impl2::update_candy_display_animation() {
	if(animation_time < 1.0) {
		animation_time += 0.02;
		if(animation_time > 1.0) animation_time = 1.0;
	}

	auto r = (animation_time - 1) * (animation_time - 1) * (animation_time - 1) + bn::fixed(1.0);

	hovered_candy->set_x(start_x + (-start_x * r));
	hovered_candy->set_y(start_y + (-start_y * r));
	hovered_candy->set_rotation(start_rotation + (-start_rotation * r));
	hovered_candy->set_scale(1.0 + r);
}

DH_END_NAMESPACE
