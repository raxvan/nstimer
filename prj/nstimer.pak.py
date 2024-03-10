
def configure(cfg):
	cfg.type("lib")
	cfg.trylink("testing.pak.py")


def construct(ctx):
	
	ctx.folder("public include: ../incl")

	ctx.fscan("src: ../incl")
	ctx.fscan("src: ../src")

	if ctx.module_enabled("testing"):
		ctx.set("public define:NSTIMER_TESTING")

