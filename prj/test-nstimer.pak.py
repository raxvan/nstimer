
def construct(ctx):
	
	ctx.prop("type","exe")
	ctx.prop("define global: TESTING_BUILD")

	ctx.fscan("src: ../test")

	ctx.dependency("nstimer.pak.py")