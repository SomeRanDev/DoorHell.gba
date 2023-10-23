#pragma once

#include "dh/dh_defines.h"

#include "bn_regular_bg_item.h"

#include "bn_regular_bg_items_dh_high_bell_1.h"
#include "bn_regular_bg_items_dh_high_bell_2.h"
#include "bn_regular_bg_items_dh_high_bell_3.h"
#include "bn_regular_bg_items_dh_high_bell_4.h"

DH_START_NAMESPACE

// ---------------------------------------------------------------
// FRAMES

#define ITEM(INDEX) &bn::regular_bg_items::dh_high_bell_ ## INDEX

constexpr int dh_high_bell_first_index = 64;
constexpr bn::regular_bg_item const* dh_high_bell_frames[] = {
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, ITEM(1), ITEM(2), ITEM(3), ITEM(4)
};

#undef ITEM

DH_END_NAMESPACE