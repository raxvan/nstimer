
import srcbuild

ctx = srcbuild.Generator()

ctx.run(
	kind = "exe",
	depends = [
		"prj.nstimer.py"
	],
	src = ctx.glob("test",[".cpp",".h"])
)
