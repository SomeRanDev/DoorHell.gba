/**
	Generates the `include/dh/dh_intro.h` file

	Run using deno:
	deno run --allow-read=graphics --allow-write=include generate_frame_h.ts
**/

import { existsSync } from "https://deno.land/std/fs/mod.ts";

function bmp_path(i: number): string {
	return `./graphics/dh/frames/dh_frame_${i}.bmp`;
}

const includes = [];
const items = [];

let i = 1;
while(existsSync(bmp_path(i))) {
	includes.push(`#include "bn_regular_bg_items_dh_frame_${i}.h"`);
	items.push(`ITEM(${i})`);
	i++;
}

const output = `#pragma once

#include "dh/dh_defines.h"

#include "bn_regular_bg_item.h"
#include "bn_regular_bg_tiles_item.h"

${includes.join("\n")}

DH_START_NAMESPACE

// ---------------------------------------------------------------
// FRAMES

#define ITEM(INDEX) &bn::regular_bg_items::dh_frame_ ## INDEX

using bg_tiles_item_const_ptr = bn::regular_bg_item const*;

//constexpr bn::regular_bg_item const* first_bg = &bn::regular_bg_items::dh_frame_1;

constexpr bg_tiles_item_const_ptr frames[] = {
	${items.join(", ")}
};

#undef ITEM

// ---------------------------------------------------------------
// INTRO FRAME COUNT

constexpr int intro_frame_count = 15;

constexpr int game_frame_start = intro_frame_count;
constexpr int game_frame_end = ${items.length - 1};
constexpr int game_frame_count = ${items.length} - intro_frame_count;

DH_END_NAMESPACE
`;

Deno.writeTextFileSync("./include/dh/dh_intro.h", output);
