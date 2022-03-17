all:
	make -C src
	make -C builders
	cp builders/agent .
