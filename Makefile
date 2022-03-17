all:
	make -C src
	make -C builders_smart
	cp builders_smart/agent .
