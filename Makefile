build:
	make -C hbuf
	make -C hstack
	make -C hqueue

test:
	make -C hbuf test
	make -C hstack test
	make -C hqueue test

clean:
	make -C hbuf clean
	make -C hstack clean
	make -C hqueue test
