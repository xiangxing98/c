NAME = buf
CC = cc
INC = ./
SRC = ./buf.c ./test.c

$(NAME):
	$(CC) $(SRC) -o $(NAME) -g -I$(INC)

test:
	touch $(NAME).log
	env MALLOC_TRACE=$(NAME).log ./$(NAME)
	@echo "memory leaks check result:"
	mtrace $(NAME) ${NAME}.log
	rm $(NAME).log

clean:
	rm -rf *.o $(NAME)

run: $(NAME)
	./$(NAME)
