/**
	cls && deno run --allow-read --allow-write generate_palette.ts Icon1.png
**/

import { decode } from "https://deno.land/x/pngs/mod.ts";
import { existsSync } from "https://deno.land/std/fs/mod.ts";

import * as path from "https://deno.land/std@0.188.0/path/mod.ts";

const __dirname = path.dirname(path.fromFileUrl(import.meta.url));

const icons: string[] = [];
const switchCases: string[] = [];
for(let i = 1; i <= 11; i++) {
	icons.push(await getIconColors(i));
	switchCases.push(`case ${i}: return icon_${i};`);
}

switchCases.push(`default: return icon_1;`);

await Deno.writeTextFile(`${__dirname}/../../include/dh/animations/dh_part_2_intro_palettes.h`, `#pragma once

#include "dh_defines.h"

#include "bn_bpp_mode.h"
#include "bn_bg_palette_item.h"
#include "bn_color.h"
#include "bn_span.h"

DH_START_ANIMATIONS_NAMESPACE

${icons.join("\n\n")}

constexpr bn::color const* get_icon(int index) {
	switch(index) {
		${switchCases.join("\n\t\t")}
	}
}

constexpr bn::span<const bn::color> get_icon_span(int index) {
	return bn::span(animations::get_icon(index), 64);
}

constexpr bn::bg_palette_item get_palette_from_icon(int index) {
	return bn::bg_palette_item(animations::get_icon_span(index), bn::bpp_mode::BPP_8);
}

DH_END_NAMESPACE
`);

/**
 * Generate C++ constexpr bn::color array from index of IconX.png
 */
async function getIconColors(index: number): string {
	const inputPath = "Icon" + index + ".png";
	const colors = await getColors(inputPath);
	return `constexpr bn::color icon_${index}[] = {
	${colors}
};`;
}

/**
 * Generate C++ bn::color array members from .png
 */
async function getColors(path: string): string {
	const file = await Deno.readFile(__dirname + "/" + path);
	const data = decode(file).image;

	const width = 8;
	const height = 12;
	const xStart = 1;
	const yStart = 2;
	const indexStart = (width * yStart) + xStart;

	const colors = [`bn::color(0, 0, 0)`];

	for(let i = indexStart; i < 79; i++) {
		if(i === 23 || i === 72 || i === 79) {
		} else {
			let index = i * 4;
			const r = data[index++];
			const g = data[index++];
			const b = data[index++];
			const a = data[index++];

			if(a === 0) {
				colors.push(`bn::color(31, 31, 31)`);
			} else {
				const rr = Math.floor(32 * (r / 255));
				const gg = Math.floor(32 * (g / 255));
				const bb = Math.floor(32 * (b / 255));
				colors.push(`bn::color(${rr}, ${gg}, ${bb})`);
			}

		}
	}

	colors.push(`bn::color(31, 31, 31)`);
	colors.push(`bn::color(16, 3, 7)`); // Phone color
	colors.push(`bn::color(0, 0, 0)`);

	return colors.join(",");
}


