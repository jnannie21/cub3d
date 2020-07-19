CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
MAIN_SOURCES = 	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c		\
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c		\
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c		\
				ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c	\
				ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c		\
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c			\
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SOURCES =	ft_lstnew.c	ft_lstadd_front.c ft_lstsize.c ft_lstlast.c				\
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c			\
				ft_lstmap.c															\
				ft_strpbrk.c ft_itoa_base.c ft_strspn.c ft_wctomb.c ft_strchrnul.c	\
				ft_pow10.c ft_ftoa.c ft_count_exp10.c ft_is_double_special.c		\
				ft_strjoin_wrap.c ft_u_itoa_base.c ft_strtolower.c ft_strcpytoend.c	\
				ft_fill_in.c
HEADER = libft.h
NAME = libft.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(MAIN_SOURCES:.c=.o) $(BONUS_SOURCES:.c=.o)
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
endif

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar cr $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

bonus:
	$(MAKE) DO_BONUS=1

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus
