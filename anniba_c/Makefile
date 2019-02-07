CC		=	gcc
LDFLAGS		=	-shared
CFLAGS		=	-W -Wall -Werror -fPIC
RM		=	rm -f
NAME		=	libmy_malloc_Linux.so
SRC 		=	my_malloc.c
OBJ		=	$(SRC:.c=.o)

.PHONY:	all

all:	${NAME}

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(SRC:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY:	clean

clean:
	-${RM} ${OBJ} $(SRC:.c=.d)

fclean:
	-${RM} ${OBJ} ${NAME} $(SRC:.c=.d)

re:	clean all
