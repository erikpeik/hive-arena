all:
	make -C src
	make -C wax_builders
	cp wax_builders/agent .
