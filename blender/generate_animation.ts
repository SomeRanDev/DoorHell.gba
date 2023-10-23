/**
	Copies a segment from ./Output to use as an animation.
	Generates its header file and converts the files from .png to .bmp

	One argument:
	generate_animation.ts <name> <start index> <end index> <required camera position index>

	Run using deno:
	deno run --allow-read --allow-write generate_animation.ts dh_close_bell_press 110 116 26
	deno run --allow-read --allow-write generate_animation.ts dh_right_bell_press 140 150 54
	deno run --allow-read --allow-write generate_animation.ts dh_high_bell_press 170 180 68
**/

import { existsSync } from "https://deno.land/std/fs/mod.ts";
import { decode as pngDecode } from "https://deno.land/x/pngs/mod.ts";
import { BitmapEncoder } from "./Encoder.ts";
import { Buffer as NodeBuffer } from "https://deno.land/x/node_buffer@1.1.0/mod.ts";

function bmpEncode(imgData: { data: Uint8Array, width: number, height: number }) {
	const arr: number[] = [];
	const inputData = imgData.data;

	const r = inputData[0];
	const g = inputData[1];
	const b = inputData[2];
	const a = inputData[3];

	function isClose(n: number) { return n >= -1 && n <= 1; }
	function isTransparent(index: number) {
		return isClose(inputData[index] - r) && isClose(inputData[index+1] - g) && isClose(inputData[index+2] - b);
	}
	
	for(let i = 0; i < inputData.length; i += 4) {
		if(isTransparent(i)) {
			arr.push(255); arr.push(255); arr.push(255); arr.push(0);
		} else {
			arr.push(inputData[i + 3]);
			arr.push(inputData[i + 2]);
			arr.push(inputData[i + 1]);
			arr.push(inputData[i]);
		}
	}

	const encoder = new BitmapEncoder({
		data: NodeBuffer.from(arr),
		width: imgData.width,
		height: imgData.height
	});
    const data = encoder.encode();

    return {
        data: data,
        width: imgData.width,
        height: imgData.height
    };
}

// Check there are 4 arguments
if(Deno.args.length !== 4) {
	throw "Missing arguments.";
}

// Get arguments
const name = Deno.args[0];
const startIndex = parseInt(Deno.args[1]);
const endIndex = parseInt(Deno.args[2]);
const requiredCameraPos = parseInt(Deno.args[3]);

/**
 * Gets the path to the ./Output png file given its index
 * 
 * @param i The index of the image
 * @returns The image path relative to .js file
 */
function getFrame(i: number): string {
	return `./Output/Frame${("" + i).padStart(4, "0")}.png`;
}

// Generate graphics folder
const outputFolder = `../graphics/dh/${name}`;
if(!existsSync(outputFolder)) {
	Deno.mkdir(outputFolder, { recursive: true });
}

// Filled in `processImage`.
const includes = [];
const items = [];

/**
 * Processes an image given its index in ./Output
 * 
 * @param index The image index to process
 */
async function processImage(index: number) {
	const outputIndex = (index - startIndex) + 1;
	const imageName = `${name}_${outputIndex}`;
	const outPath = `${outputFolder}/${imageName}`;

	// Convert .png to .bmp
	const pngFile = await Deno.readFile(getFrame(index));
	const pngData = pngDecode(pngFile);
	const bitmap = bmpEncode({
		data: pngData.image,
		width: pngData.width,
		height: pngData.height
	});
	Deno.writeFileSync(`${outPath}.bmp`, bitmap.data);

	// Generate .json
	Deno.writeTextFileSync(`${outPath}.json`, `{
	"type": "regular_bg",
	"bpp_mode": "bpp_4"
}`);

	// Generate header data
	includes.push(`#include "bn_regular_bg_items_${imageName}.h"`);
	items.push(`ITEM(${outputIndex})`);
}

// Process images from start to end
for(let i = startIndex; i <= endIndex; i++) {
	if(existsSync(getFrame(i))) {
		await processImage(i);
	}
}

// Ensure include path exists for header file
const includePath = `../include/dh/animations`;
if(!existsSync(includePath)) {
	Deno.mkdir(includePath, { recursive: true });
}

// Generate header file
Deno.writeTextFileSync(`${includePath}/${name}.h`, `#pragma once

#include "dh/dh_defines.h"

#include "bn_regular_bg_item.h"

${includes.join("\n")}

DH_START_ANIMATIONS_NAMESPACE

// ---------------------------------------------------------------
// FRAMES

#define ITEM(INDEX) &bn::regular_bg_items::${name}_ ## INDEX

constexpr int ${name}_data[] = {
	${includes.length}, ${(requiredCameraPos - 16) % 14}, ${Math.floor((requiredCameraPos - 16) / 14) * 4}
};
constexpr bn::regular_bg_item const* ${name}_frames[] = {
	${items.join(", ")}
};

#undef ITEM

DH_END_NAMESPACE
`)