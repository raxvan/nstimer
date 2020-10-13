
import srcbuild

ctx = srcbuild.Generator()

ctx.run("exe",
	diagnostics = True,
	depends = [
		"prj.nstimer.py"
	],
	src = ctx.glob("test",[".cpp",".h"])
)
