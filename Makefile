CC = gcc
CFLAGS = -c -g -Wall -Wextra -Werror
#LIBS = -Lminilibx/ -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd
LIBS = -Lminilibx/ -lmlx -lXext -lX11 -lm -lbsd
MAIN_SOURCES =	cb_cub3d.c
BONUS_SOURCES = 
NAME = cub3D
MINILIBX = minilibx/libmlx.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(BONUS_SOURCES:.c=.o)
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
endif

all: makeminilibx $(NAME)

$(NAME): $(OBJECTS) $(MINILIBX)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

bonus:
	$(MAKE) DO_BONUS=1

makeminilibx:
	$(MAKE) -C minilibx/

clean:
	$(MAKE) clean -C minilibx/
	rm -f *.o

fclean: clean
	$(MAKE) clean -C minilibx/
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus makeminilibx
