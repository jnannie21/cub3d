CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
LIBS = -Lminilibx/ -lmlx -Llibft/ -lft -lXext -lX11 -lm
PARSE_DIR =			parse
DRAW_DIR =			draw
PARSE_FILES =		cb_parse_map_file.c cb_parse_map.c cb_check_walls.c			\
					cb_parse_settings.c cb_print_map.c cb_read_color.c
DRAW_FILES =		cb_draw_frame.c cb_draw_sprites.c cb_draw_walls.c			\
					cb_print_floor_and_ceilling.c cb_draw_walls_utils.c
PARSE_SOURCES =		$(patsubst %, $(PARSE_DIR)/%, $(PARSE_FILES))
DRAW_SOURCES =		$(patsubst %, $(DRAW_DIR)/%, $(DRAW_FILES))
MAIN_SOURCES =		cb_cub3d.c cb_hooks.c $(PARSE_SOURCES) $(DRAW_SOURCES)		\
					cb_save_frame.c cb_motion.c cb_exit.c cb_free_map.c
PARSE_BONUS_FILES =	cb_parse_map_file_bonus.c cb_parse_map_bonus.c 				\
					cb_check_walls_bonus.c cb_parse_settings_bonus.c			\
					cb_print_map_bonus.c cb_read_color_bonus.c
DRAW_BONUS_FILES =	cb_draw_frame_bonus.c cb_draw_sprites_bonus.c				\
					cb_draw_walls_bonus.c cb_print_floor_and_ceilling_bonus.c	\
					cb_draw_walls_utils_bonus.c
PARSE_BONUS_SOURCES =	$(patsubst %, $(PARSE_DIR)/%, $(PARSE_BONUS_FILES))
DRAW_BONUS_SOURCES =	$(patsubst %, $(DRAW_DIR)/%, $(DRAW_BONUS_FILES))
BONUS_SOURCES =		cb_cub3d_bonus.c cb_hooks_bonus.c $(PARSE_BONUS_SOURCES)	\
					$(DRAW_BONUS_SOURCES) cb_save_frame_bonus.c					\
					cb_motion_bonus.c cb_exit_bonus.c cb_free_map_bonus.c
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

.PHONY: all clean fclean bonus re set_rights