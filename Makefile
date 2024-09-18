SRC = $(shell find src/ -name "*.c") # va recuperer tous les fichiers .c contenue dans src
OBJ = $(SRC:.c=.o) # va transformer les fichier .c en fichier .o
NAME = my_tar
COMPILER = gcc
INCLUDE = -I ./include/
FLAGS = -Wall -Werror -Wextra

all : $(OBJ) # compile tous y compris le binaire final
	$(COMPILER) $(OBJ) -o $(NAME) $(FLAGS)

re :	fclean all

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

.c.o:
	$(COMPILER) $(FLAGS) -c $< -o $@ $(INCLUDE)
