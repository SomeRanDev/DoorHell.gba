#pragma once

#include "dh/dh_defines.h"

#include "bn_regular_bg_item.h"

#include "bn_regular_bg_items_dh_close_left_bell_1.h"
#include "bn_regular_bg_items_dh_close_left_bell_2.h"
#include "bn_regular_bg_items_dh_close_left_bell_3.h"
#include "bn_regular_bg_items_dh_close_left_bell_4.h"

DH_START_NAMESPACE

// ---------------------------------------------------------------
// FRAMES

#define ITEM(INDEX) &bn::regular_bg_items::dh_close_left_bell_ ## INDEX

constexpr int dh_close_left_bell_first_index = 15;
constexpr bn::regular_bg_item const* dh_close_left_bell_frames[] = {
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, ITEM(1), ITEM(2), ITEM(3), ITEM(4), nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

#undef ITEM

DH_END_NAMESPACE
