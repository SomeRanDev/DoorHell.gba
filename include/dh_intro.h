#pragma once

#include "dh_defines.h"

#include "bn_regular_bg_item.h"

#include "bn_regular_bg_items_dh_intro_1.h"
#include "bn_regular_bg_items_dh_intro_2.h"
#include "bn_regular_bg_items_dh_intro_3.h"
#include "bn_regular_bg_items_dh_intro_4.h"
#include "bn_regular_bg_items_dh_intro_5.h"
#include "bn_regular_bg_items_dh_intro_6.h"
#include "bn_regular_bg_items_dh_intro_7.h"
#include "bn_regular_bg_items_dh_intro_8.h"
#include "bn_regular_bg_items_dh_intro_9.h"
#include "bn_regular_bg_items_dh_intro_10.h"
#include "bn_regular_bg_items_dh_intro_11.h"
#include "bn_regular_bg_items_dh_intro_12.h"
#include "bn_regular_bg_items_dh_intro_13.h"
#include "bn_regular_bg_items_dh_intro_14.h"
#include "bn_regular_bg_items_dh_intro_15.h"
// #include "bn_regular_bg_items_dh_intro_16.h"
// #include "bn_regular_bg_items_dh_intro_17.h"
// #include "bn_regular_bg_items_dh_intro_18.h"
// #include "bn_regular_bg_items_dh_intro_19.h"
// #include "bn_regular_bg_items_dh_intro_20.h"
// #include "bn_regular_bg_items_dh_intro_21.h"
// #include "bn_regular_bg_items_dh_intro_22.h"
// #include "bn_regular_bg_items_dh_intro_23.h"
// #include "bn_regular_bg_items_dh_intro_24.h"
// #include "bn_regular_bg_items_dh_intro_25.h"

DH_START_NAMESPACE

// ---------------------------------------------------------------
// INTRO FRAMES

#define ITEM(INDEX) &bn::regular_bg_items::dh_intro_ ## INDEX

using bg_item_const_ptr = bn::regular_bg_item const*;

constexpr bg_item_const_ptr intro_frames[] = {
	ITEM(1), ITEM(2), ITEM(3), ITEM(4), ITEM(5),
	ITEM(6), ITEM(7), ITEM(8), ITEM(9), ITEM(10), 
	ITEM(11), ITEM(12), ITEM(13), ITEM(14), ITEM(15),
	// ITEM(16), ITEM(17), ITEM(18), ITEM(19), ITEM(20), 
	// ITEM(21), ITEM(22), ITEM(23), ITEM(24), ITEM(25), 
};

#undef ITEM

// ---------------------------------------------------------------
// INTRO FRAME COUNT

constexpr int intro_frame_count = 15;//25;

DH_END_NAMESPACE
