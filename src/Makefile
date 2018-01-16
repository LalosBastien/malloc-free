ENV = $(echo uname)
NAME = libmy_malloc
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

CC = gcc
CFLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
RM = rm -rf

.PHONY: all clean

all:
		make $(NAME) clean

$(NAME):	$(OBJECTS)
		$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
		$(RM) $(OBJECTS)

fclean:		clean
		$(RM) $(NAME)
re:
		fclean all
