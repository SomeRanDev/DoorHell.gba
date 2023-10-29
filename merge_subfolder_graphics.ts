/**
 * Merges all the subfolders together into a folder called "merge".
 * Used for the submission version of the game.
 * 
 * deno run --allow-read --allow-write merge_subfolder_graphics.ts
 */

import { existsSync } from "https://deno.land/std/fs/mod.ts";

const filesToCopy: [string, string][] = [];

const graphicsDir = "graphics/dh";

Deno.readDirSync(graphicsDir).forEach(item => {
	const itemName = item.name;
	const p = `${graphicsDir}/${item.name}`;
	if(Deno.lstatSync(p).isDirectory) {
		Deno.readDirSync(p).forEach(subgraphic => {
			const subname = subgraphic.name;
			if(subname.endsWith(".json") || subname.endsWith(".bmp")) {
				filesToCopy.push([`${graphicsDir}/${itemName}/${subname}`, subname]);
			}
		});
	}
});

if(!existsSync("graphics/merged")) {
	Deno.mkdirSync("graphics/merged");
}

for(const f of filesToCopy) {
	Deno.copyFileSync(f[0], `graphics/merged/${f[1]}`);
}
