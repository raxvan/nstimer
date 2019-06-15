
import srcbuild

ctx = srcbuild.Generator()

ctx.run(
	kind = "lib",
	incl = [
		"include"
	],
	src = 
		ctx.glob("impl",[".cpp",".h"]) + 
		ctx.glob("include",[".cpp",".h"])
)
