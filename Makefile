CC = gcc
CFLAGS = -c -g -Wall -Wextra -Werror
#LIBS = -Lminilibx/ -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd
LIBS = -Lminilibx/ -lmlx -Llibft/ -lft -lXext -lX11 -lm -lbsd
MAIN_SOURCES =	cb_cub3d.c cb_parse_map_file.c get_next_line.c			\
				cb_parse_map.c cb_parse_settings.c cb_events_handlers.c
BONUS_SOURCES = 
HEADERS = cb_cub3d.h
NAME = cub3D
MINILIBX = minilibx/libmlx.a
LIBFT = libft/libft.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(BONUS_SOURCES:.c=.o)
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
endif

all: $(NAME)

$(NAME): $(OBJECTS) $(MINILIBX) $(LIBFT)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

bonus:
	$(MAKE) DO_BONUS=1

$(MINILIBX):
	$(MAKE) -C minilibx/

$(LIBFT):
	$(MAKE) bonus -C libft/

clean:
	$(MAKE) clean -C minilibx/
	$(MAKE) clean -C libft/
	rm -f *.o

fclean:
	$(MAKE) clean -C minilibx/
	$(MAKE) fclean -C libft/
	rm -f *.o
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus
