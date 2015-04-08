# vim:set noet:

all:
	make all -C t

%:
	make $@ -C t
