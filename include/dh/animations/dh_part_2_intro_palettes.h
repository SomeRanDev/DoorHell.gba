#pragma once

#include "dh_defines.h"

#include "bn_bpp_mode.h"
#include "bn_bg_palette_item.h"
#include "bn_color.h"
#include "bn_span.h"

DH_START_ANIMATIONS_NAMESPACE

constexpr bn::color icon_1[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(18, 6, 23),bn::color(18, 6, 23),bn::color(13, 4, 17),bn::color(13, 4, 17),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(13, 4, 17),bn::color(13, 4, 17),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(13, 4, 17),bn::color(18, 6, 23),bn::color(13, 4, 17),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(13, 4, 17),bn::color(18, 6, 23),bn::color(31, 31, 31),bn::color(13, 4, 17),bn::color(31, 31, 31),bn::color(18, 6, 23),bn::color(13, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(13, 4, 17),bn::color(18, 6, 23),bn::color(18, 6, 23),bn::color(18, 6, 23),bn::color(13, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(13, 4, 17),bn::color(13, 4, 17),bn::color(13, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_2[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(17, 1, 12),bn::color(24, 4, 17),bn::color(17, 1, 12),bn::color(24, 4, 17),bn::color(17, 1, 12),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(24, 4, 17),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(17, 1, 12),bn::color(31, 31, 31),bn::color(17, 1, 12),bn::color(31, 31, 31),bn::color(17, 1, 12),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_3[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 4, 6),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(18, 4, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 4, 6),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(18, 4, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 4, 6),bn::color(18, 4, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_4[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(22, 13, 11),bn::color(13, 6, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(13, 6, 6),bn::color(13, 6, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(13, 6, 6),bn::color(13, 6, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(13, 6, 6),bn::color(13, 6, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(17, 9, 8),bn::color(13, 6, 6),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_5[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 15, 7),bn::color(25, 15, 7),bn::color(25, 15, 7),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 15, 7),bn::color(31, 23, 10),bn::color(31, 23, 10),bn::color(25, 15, 7),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 15, 7),bn::color(31, 23, 10),bn::color(25, 15, 7),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 15, 7),bn::color(31, 23, 10),bn::color(25, 15, 7),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 15, 7),bn::color(31, 23, 10),bn::color(31, 23, 10),bn::color(25, 15, 7),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 15, 7),bn::color(25, 15, 7),bn::color(25, 15, 7),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_6[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(13, 18, 4),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(13, 18, 4),bn::color(13, 18, 4),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(13, 18, 4),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(13, 18, 4),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(18, 23, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(13, 18, 4),bn::color(13, 18, 4),bn::color(13, 18, 4),bn::color(13, 18, 4),bn::color(13, 18, 4),bn::color(13, 18, 4),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_7[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(10, 26, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(10, 26, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(5, 21, 4),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(5, 21, 4),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(5, 21, 4),bn::color(3, 15, 3),bn::color(5, 21, 4),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(5, 21, 4),bn::color(5, 21, 4),bn::color(9, 5, 3),bn::color(3, 15, 3),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(3, 15, 3),bn::color(12, 8, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(12, 8, 5),bn::color(9, 5, 3),bn::color(12, 8, 5),bn::color(9, 5, 3),bn::color(9, 5, 3),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_8[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(12, 30, 26),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(12, 30, 26),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(12, 30, 26),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(12, 30, 26),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(2, 18, 20),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(2, 18, 20),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(2, 18, 20),bn::color(2, 18, 20),bn::color(2, 18, 20),bn::color(2, 18, 20),bn::color(2, 18, 20),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(2, 26, 25),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_9[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(11, 9, 15),bn::color(21, 19, 25),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(21, 19, 25),bn::color(11, 9, 15),bn::color(31, 31, 31),bn::color(11, 9, 15),bn::color(21, 19, 25),bn::color(11, 9, 15),bn::color(5, 4, 8),bn::color(5, 4, 8),bn::color(11, 9, 15),bn::color(21, 19, 25),bn::color(11, 9, 15),bn::color(7, 7, 11),bn::color(11, 9, 15),bn::color(21, 19, 25),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(21, 19, 25),bn::color(11, 9, 15),bn::color(7, 7, 11),bn::color(31, 31, 31),bn::color(7, 7, 11),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(11, 9, 15),bn::color(7, 7, 11),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(7, 7, 11),bn::color(7, 7, 11),bn::color(7, 7, 11),bn::color(7, 7, 11),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_10[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 5, 8),bn::color(25, 5, 8),bn::color(25, 18, 5),bn::color(25, 18, 5),bn::color(25, 18, 5),bn::color(25, 5, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(25, 18, 5),bn::color(25, 18, 5),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(25, 18, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(10, 26, 5),bn::color(10, 26, 5),bn::color(10, 22, 26),bn::color(10, 22, 26),bn::color(10, 22, 26),bn::color(10, 26, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(10, 22, 26),bn::color(10, 22, 26),bn::color(15, 10, 16),bn::color(15, 10, 16),bn::color(15, 10, 16),bn::color(10, 22, 26),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(15, 10, 16),bn::color(15, 10, 16),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(15, 10, 16),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color icon_11[] = {
	bn::color(0, 0, 0),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(8, 10, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(8, 10, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(4, 7, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(4, 7, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(8, 10, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(8, 10, 8),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(4, 7, 5),bn::color(8, 10, 8),bn::color(8, 10, 8),bn::color(4, 7, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(4, 7, 5),bn::color(4, 7, 5),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(31, 31, 31),bn::color(16, 3, 7),bn::color(0, 0, 0)
};

constexpr bn::color const* get_icon(int index) {
	switch(index) {
		case 1: return icon_1;
		case 2: return icon_2;
		case 3: return icon_3;
		case 4: return icon_4;
		case 5: return icon_5;
		case 6: return icon_6;
		case 7: return icon_7;
		case 8: return icon_8;
		case 9: return icon_9;
		case 10: return icon_10;
		case 11: return icon_11;
		default: return icon_1;
	}
}

constexpr bn::span<const bn::color> get_icon_span(int index) {
	return bn::span(animations::get_icon(index), 64);
}

constexpr bn::bg_palette_item get_palette_from_icon(int index) {
	return bn::bg_palette_item(animations::get_icon_span(index), bn::bpp_mode::BPP_8);
}

DH_END_NAMESPACE
