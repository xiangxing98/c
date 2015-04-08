.PHONY: all clean test

TARGETS := hbuf hdict hlist hqueue hstack

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
	$(CC) t_$@.c ../src/$@.c -o $@ $(CFLAGS) -I ../src
	$(call runtest, $@)
