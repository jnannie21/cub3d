CC = gcc
CFLAGS = -c -g -Wall -Wextra -Werror
LIBS = -Lminilibx/ -lmlx -Llibft/ -lft -lXext -lX11 -lm
MAIN_SOURCES =	cb_cub3d.c parse/cb_parse_map_file.c parse/cb_parse_map.c			\
				parse/cb_parse_settings.c parse/cb_print_map.c cb_hooks.c			\
				draw/cb_draw_frame.c draw/cb_draw_sprites.c draw/cb_draw_walls.c	\
				draw/cb_print_floor_and_ceilling.c draw/cb_draw_walls_utils.c		\
				cb_save_frame.c cb_motion.c
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
	rm -f draw/*.o
	rm -f parse/*.o
	rm -f *.o

fclean:
	$(MAKE) clean -C minilibx/
	$(MAKE) fclean -C libft/
	rm -f draw/*.o
	rm -f parse/*.o
	rm -f *.o
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus
