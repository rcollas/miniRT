SRCS		= ft_memset.c\
			  ft_bzero.c\
			  ft_memcpy.c\
			  ft_memccpy.c\
			  ft_memmove.c\
			  ft_memchr.c\
			  ft_memcmp.c\
			  ft_strlen.c\
			  ft_isalpha.c\
			  ft_isdigit.c\
			  ft_isalnum.c\
			  ft_isascii.c\
			  ft_isprint.c\
			  ft_toupper.c\
			  ft_tolower.c\
			  ft_strchr.c\
			  ft_strrchr.c\
			  ft_strncmp.c\
			  ft_strlcpy.c\
			  ft_strlcat.c\
			  ft_strnstr.c\
			  ft_atoi.c\
			  ft_calloc.c\
			  ft_strdup.c\
			  ft_substr.c\
			  ft_strjoin.c\
			  ft_strtrim.c\
			  ft_split.c\
			  ft_itoa.c\
			  ft_strmapi.c\
			  ft_putchar_fd.c\
			  ft_putstr_fd.c\
			  ft_putendl_fd.c\
			  ft_putnbr_fd.c\

BONUS		= ft_lstnew.c\
			  ft_lstadd_front.c\
			  ft_lstsize.c\
			  ft_lstlast.c\
			  ft_lstadd_back.c\
			  ft_lstdelone.c\
			  ft_lstclear.c\
			  ft_lstiter.c\
			  ft_lstmap.c\

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS:.c=.o)

NAME		= libft.a

CC			= gcc

RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -Iincludes

RESET		= \033[0m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
WHITE		= \033[1;37m

all:		$(NAME)

%.o : %.c
	@${CC} -c ${CFLAGS} $< -o $@

$(NAME):	$(OBJS)
				@ar rc $(NAME) $^
				@echo "$(YELLOW)$(NAME) created$(RESET)"
				@ranlib $(NAME)

bonus:		$(OBJS) $(OBJS_BONUS)
				@ar rc $(NAME) $^ 
				@echo "$(YELLOW)$(NAME) bonus created$(RESET)"
				@ranlib $(NAME)

clean:
				@${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
				@${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
