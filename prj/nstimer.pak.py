
def construct(ctx):
	
	ctx.prop("type","lib")

	ctx.path("public include: ../include")

	ctx.fscan("src: ../include")
	ctx.fscan("src: ../impl")

