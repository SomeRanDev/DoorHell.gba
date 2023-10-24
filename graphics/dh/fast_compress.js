const folder = process.argv[2];

const fs = require("fs");

const noCompress = `{
	"type": "regular_bg",
	"bpp_mode": "bpp_4"
}`;

const compress = `{
	"type": "regular_bg",
	"bpp_mode": "bpp_4",
	"compression": "auto"
}`;

const makeNotCompressed = process.argv[3] === "true";
const target = makeNotCompressed ? compress : noCompress;
const result = makeNotCompressed ? noCompress : compress;

if(fs.existsSync(folder)) {
	fs.readdirSync(folder).forEach(function(file) {
		if(file.endsWith(".json")) {
			const data = fs.readFileSync(folder + "/" + file).toString();
			if(data.trim() === target) {
				fs.writeFileSync(folder + "/" + file, result);
			}
		}
	});
}
