NAME = ft_ls

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES =	-I ./includes/\
			-I ./libft/

SRCS =	src/main.c\
		src/ctx.c\
		src/ctx_parse.c\
		src/files/files_add_back.c\
		src/files/files_last.c\
		src/files/files_new.c\
		src/files/files_size.c\
		src/files/files_free.c\
		src/read.c\
		src/sort.c\
		src/display.c

OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJDIR)/%.d)

LIBFT = ./libft/libft.a

all: $(LIBFT)
	@make -j compile --no-print-directory

compile: $(NAME)

re: fclean all

$(LIBFT):
	@make -C ./libft all --no-print-directory

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT) -ltermcap

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	@make -C ./libft clean --no-print-directory
	@echo Cleaning objects
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C ./libft fclean --no-print-directory
	@echo Cleaning $(NAME)
	@rm -rf $(NAME)

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run

-include $(DEPS)
