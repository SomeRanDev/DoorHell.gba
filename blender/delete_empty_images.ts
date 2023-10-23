/**
	Copies non-empty images and generates a header file for them.

	Example:
	deno run --allow-read --allow-write delete_empty_images.ts dh_high_bell
**/

import { decode } from "https://deno.land/x/pngs/mod.ts";
import { existsSync } from "https://deno.land/std/fs/mod.ts";

function getFrame(i: number): string {
	return `./Output/Frame${("" + i).padStart(4, "0")}.png`;
}

if(Deno.args.length !== 1) {
	throw "Missing name argument.";
}

const name = Deno.args[0];

const keptFiles: [string, number] = [];
const toBeRemoved: string[] = [];

let imageIndex = 1;
while(existsSync(getFrame(imageIndex))) {
	await checkImage(imageIndex);
	imageIndex++;
}

async function checkImage(imageIndex: number) {
	const path = getFrame(imageIndex);
	const file = await Deno.readFile(path);
	const data = decode(file).image;

	const r = data[0];
	const g = data[1];
	const b = data[2];
	const a = data[3];

	function irrelevant(num: number) {
		return num >= -1 && num <= 1;
	}

	let i = 0;
	while(i < data.length) {
		if(
			!irrelevant(data[i++] - r) ||
			!irrelevant(data[i++] - g) ||
			!irrelevant(data[i++] - b) ||
			!irrelevant(data[i++] - a)
		) {
			keptFiles.push([path, imageIndex]);
			return;
		}
	}

	// await Deno.remove(path);
	toBeRemoved.push(path);
}

// -----------------------------------------------------------------
// GENERATE HEADER

const arrayMembers = [];
for(let i = 0; i < imageIndex - 1; i++) {
	arrayMembers.push("nullptr");
}

const folderName = `${name}_out`;
if(!existsSync("./" + folderName)) {
	Deno.mkdir("./" + folderName);
}
if(!existsSync(`./${folderName}/out`)) {
	Deno.mkdir(`./${folderName}/out`);
}

let firstIndex = -1;

const includes = [];
for(let i = 0; i < keptFiles.length; i++) {
	const data = keptFiles[i];
	const imageName = `${name}_${i + 1}`;
	Deno.copyFileSync(getFrame(data[1]), `./${folderName}/${imageName}.png`);
	Deno.writeTextFileSync(`./${folderName}/out/${imageName}.json`, `{
	"type": "regular_bg",
	"bpp_mode": "bpp_4"
}`);
	includes.push(`#include "bn_regular_bg_items_${imageName}.h"`);
	if(firstIndex == -1) {
		firstIndex = data[1] - 1;
	}
	arrayMembers[data[1] - 1] = `ITEM(${i + 1})`;
}

let arrayMembersStr = "";
{
	const arrayMemberJoined = [];
	const len = Math.ceil(arrayMembers.length / 10);
	for(let i = 0; i < len; i++) {
		arrayMemberJoined.push(arrayMembers.slice(i * 10, Math.min((i + 1) * 10, arrayMembers.length)).join(", "));
	}
	arrayMembersStr = arrayMemberJoined.join(",\n\t");
}

Deno.writeTextFileSync(`../include/dh/${name}.h`, `#pragma once

#include "dh/dh_defines.h"

#include "bn_regular_bg_item.h"

${includes.join("\n")}

DH_START_NAMESPACE

// ---------------------------------------------------------------
// FRAMES

#define ITEM(INDEX) &bn::regular_bg_items::${name}_ ## INDEX

constexpr int ${name}_first_index = ${firstIndex};
constexpr bn::regular_bg_item const* ${name}_frames[] = {
	${arrayMembersStr}
};

#undef ITEM

DH_END_NAMESPACE
`)
