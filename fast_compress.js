/**
	node fast_compress.js graphics/dh/close_bell
	node fast_compress.js graphics/dh/dh_part_2_intro true bpp_8
**/

const folder = process.argv[2];
const bppMode = process.argv[4] ?? "bpp_4";

const fs = require("fs");

const noCompress = `{
	"type": "regular_bg",
	"bpp_mode": "${bppMode}"
}`;

const compress = `{
	"type": "regular_bg",
	"bpp_mode": "${bppMode}",
	"compression": "auto"
}`;

const makeNotCompressed = process.argv[3] === "true";
const target = makeNotCompressed ? compress : noCompress;
const result = makeNotCompressed ? noCompress : compress;

if(fs.existsSync(folder)) {
	fs.readdirSync(folder).forEach(function(file) {
		if(file.endsWith(".json")) {
			const data = fs.readFileSync(folder + "/" + file).toString();
			//if(data.trim() === target) {
				fs.writeFileSync(folder + "/" + file, `{
	"type": "regular_bg",
	"bpp_mode": "bpp_4",
	"compression": "auto"
}`);
			//}
		}
	});
} else {
	console.log("Folder doesn't exist: " + folder);
}
