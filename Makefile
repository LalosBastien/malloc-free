##
## Makefile for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git
## 
## Made by LALOS Bastien
## Login   <lalos_b@etna-alternance.net>
## 
## Started on  Tue Jan 16 12:56:16 2018 LALOS Bastien
## Last update Tue Feb  6 20:48:28 2018 LALOS Bastien
##

ENV = $(shell uname)
NAME = libmy_malloc_$(ENV).so
LINK_NAME = libmy_malloc.so
OBJECTS = $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
##HEADERS = $(wildcard include/*.h)

CC = gcc
CFLAGS = -ggdb -W -Wall -Werror -Wextra -ansi  -fPIC
RM = rm
LN = ln

LDFLAGS=
LDLIBS=

.PHONY: all clean

all:
		make $(NAME) link

$(NAME):	$(OBJECTS)
		$(CC) -shared -o $(NAME) $(OBJECTS)

link:
		$(LN) -snf $(NAME)$< $(LINK_NAME)$<

clean:
		$(RM) $(OBJECTS)

lclean:
		$(RM) $(LINK_NAME)

fclean:		clean lclean
		$(RM) $(NAME)

re:		fclean all

exe:		$(OBJECTS)
		$(CC) -o libmy_malloc $(OBJECTS)
