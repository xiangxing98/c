NAME = hlist
CC = cc
INC = ./
SRC = ./$(NAME).c ./test.c
OBJ = $(SRC:c=o)
UNAME := $(shell uname)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME) -I$(INC)

clean:
	rm -rf *.o $(NAME)

run: $(NAME)
	./$(NAME)

	
test: $(NAME)
ifeq ($(UNAME), Linux)
	touch $(NAME).log
	env MALLOC_TRACE=$(NAME).log ./$(NAME)
	@echo "memory leaks check result:"
	mtrace $(NAME) ${NAME}.log
	rm $(NAME).log
else
	./$(NAME)
endif
