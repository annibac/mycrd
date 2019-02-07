CC		=	gcc
LDFLAGS		=	-shared
CFLAGS		=	-W -Wall -Werror -fPIC
RM		=	rm -f
TARGET_LIB	=	libmy_malloc_Linux.so
SRC 		=	my_malloc.c
OBJ		=	$(SRC:.c=.o)

.PHONY:	all

all:	${TARGET_LIB}

$(TARGET_LIB): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(SRC:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRC:.c=.d)

.PHONY:	clean

clean:
	-${RM} ${OBJ} ${TARGET_LIB} $(SRC:.c=.d)
