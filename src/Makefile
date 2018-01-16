##
## Makefile for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
## 
## Made by LALOS Bastien
## Login   <lalos_b@etna-alternance.net>
## 
## Started on  Tue Jan 16 12:56:16 2018 LALOS Bastien
## Last update Tue Jan 16 12:56:24 2018 LALOS Bastien
##

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
