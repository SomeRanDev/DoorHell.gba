/**
	Generates the `graphics/dh/frames/dh_frame_X.json` files by copying
	the settings from `graphics/dh/frames/dh_frame_1.json`.

	Run using deno:
	deno run --allow-read=graphics --allow-write=graphics update_json_data.ts
**/

import { existsSync } from "https://deno.land/std/fs/mod.ts";

function json_path(i: number): string {
	return `./graphics/dh/frames/dh_frame_${i}.json`;
}

function bmp_path(i: number): string {
	return `./graphics/dh/frames/dh_frame_${i}.bmp`;
}

let i = 2;
const data: Uint8Array = await Deno.readFile(json_path(1));

while(existsSync(bmp_path(i))) {
	Deno.writeFileSync(json_path(i), data);
	i++;
}
