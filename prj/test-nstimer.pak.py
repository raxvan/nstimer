
def configure(cfg):
	cfg.link("../../ttf/testing.pak.py").enable()
	cfg.link("nstimer.pak.py")


def construct(ctx):
	
	ctx.config("type","exe")

	ctx.fscan("src: ../test")
