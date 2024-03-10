
def configure(cfg):
	cfg.type("exe")
	cfg.link("testing.pak.py").enable()
	cfg.link("nstimer.pak.py")

def construct(ctx):
	ctx.fscan("src: ../test")
