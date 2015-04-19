.PHONY: all clean hfs

TARGETS := buf hdict hlist hqueue hstack hfs

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
	rm -f $(TARGETS:=.o)

%: t_%.c ../src/%.c ../src/%.h ../src/bool.h
	$(CC) t_$@.c ../src/$@.c -o $@ $(CFLAGS) -I../src
	$(call runtest, $@)

hfs: t_hfs.c ../src/hfs.c ../src/hfs.h ../src/buf.c ../src/buf.h \
	../src/bool.h
	$(CC) t_hfs.c ../src/hfs.c ../src/buf.c -o hfs $(CFLAGS) -I../src
	$(call runtest, hfs)
