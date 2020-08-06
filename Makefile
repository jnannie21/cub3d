CC = gcc
CFLAGS = -c -g -Wall -Wextra -Werror
LIBS = -Lminilibx/ -lmlx -Llibft/ -lft -lXext -lX11 -lm
PARSE_DIR = parse
PARSE_FILES =	cb_parse_map_file.c cb_parse_map.c cb_check_walls.c		\
				cb_parse_settings.c cb_print_map.c
PARSE_SOURCES = $(patsubst %, $(PARSE_DIR)/%, $(PARSE_FILES))
DRAW_DIR = draw
DRAW_FILES =	cb_draw_frame.c cb_draw_sprites.c cb_draw_walls.c		\
				cb_print_floor_and_ceilling.c cb_draw_walls_utils.c
DRAW_SOURCES = $(patsubst %, $(DRAW_DIR)/%, $(DRAW_FILES))
MAIN_SOURCES =	cb_cub3d.c cb_hooks.c $(PARSE_SOURCES) $(DRAW_SOURCES)	\
				cb_save_frame.c cb_motion.c cb_exit.c cb_free_map.c
BONUS_SOURCES = 
HEADERS = cb_cub3d.h
NAME = cub3D
MINILIBX = minilibx/libmlx.a
LIBFT = libft/libft.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(MAIN_SOURCES:.c=.o) $(BONUS_SOURCES:.c=.o)
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
endif

all: set_rights $(NAME)

set_rights:
	@chmod 777 minilibx/configure

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
	rm -f frame.bmp

fclean:
	$(MAKE) clean -C minilibx/
	$(MAKE) fclean -C libft/
	rm -f draw/*.o
	rm -f parse/*.o
	rm -f *.o
	rm -f frame.bmp
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus set_rights
