.PHONY: all clean hfs

TARGETS := hbuf hdict hlist hqueue hstack hfs

ifeq ($(shell uname), Linux)
define runtest
	$(eval name := $(strip $1))
	touch $(name).log
	env MALLOC_TRACE=$(name).log ./$(name)
	mtrace $(name) $(name).log
endef
else
define runtest
	$(eval name := $(strip $1))
	./$(name)
endef
endif

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
	rm -f $(TARGETS:=.log)

%: t_%.c ../src/%.c ../src/%.h
	$(CC) t_$@.c ../src/$@.c -o $@ $(CFLAGS) -I../src
	$(call runtest, $@)

hfs: t_hfs.c ../src/hfs.c ../src/hfs.h ../src/hbuf.c ../src/hbuf.h
	touch hfs_open hfs_close
	$(CC) t_hfs.c ../src/hfs.c ../src/hbuf.c -o hfs $(CFLAGS) -I../src
	$(call runtest, hfs)
	rm -rf hfs_*
