build:
	make -C hbuf
	make -C hstack
	make -C hqueue
	make -C hlist
	make -C hdict

test:
	make -C hbuf test
	make -C hstack test
	make -C hqueue test
	make -C hlist test
	make -C hdict test

clean:
	make -C hbuf clean
	make -C hstack clean
	make -C hqueue clean
	make -C hlist clean
	make -C hdict clean
