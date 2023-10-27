const fs = require("fs");

fs.readdirSync(__dirname).forEach(function(file) {
	if(file.match(/dh_part_2_intro_phone_(\d+)\.png/i)) {
		fs.writeFileSync("dh_part_2_intro_phone_" + RegExp.$1 + ".json", `{
	"type": "regular_bg",
	"bpp_mode": "bpp_8"
}`);
	}
});
