.PHONY: all clean fs

TARGETS := buf dict list queue stack fs

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

fs: t_fs.c ../src/fs.c ../src/fs.h ../src/buf.c ../src/buf.h \
	../src/bool.h
	$(CC) t_fs.c ../src/fs.c ../src/buf.c -o fs $(CFLAGS) -I../src
	$(call runtest, fs)
