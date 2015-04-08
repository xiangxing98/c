# vim:set noet:

default: all

.DEFAULT:
	make $@ -C t
