NAME = buf
CC = cc
INC = ./
SRC = ./$(NAME).c ./test.c
OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME) -I$(INC)

clean:
	rm -rf *.o $(NAME)

run: $(NAME)
	./$(NAME)

test: $(NAME)
	touch $(NAME).log
	env MALLOC_TRACE=$(NAME).log ./$(NAME)
	@echo "memory leaks check result:"
	mtrace $(NAME) ${NAME}.log
	rm $(NAME).log
