import { decode } from "https://deno.land/x/pngs/mod.ts";
import { existsSync } from "https://deno.land/std/fs/mod.ts";

function getFrame(i: number): string {
	return `./Output/Frame${("" + i).padStart(4, "0")}.png`;
}

let imageIndex = 1;
while(existsSync(getFrame(imageIndex))) {
	await checkImage(getFrame(imageIndex));
	imageIndex++;
}

async function checkImage(path: string) {
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
			return;
		}
	}

	await Deno.remove(path);
}
