NAME = lem-in

LIBF = ./libft

LNAM = $(LIBF)/libft.a

INCL = ./includes

HEADERS = $(INCL)/lem_in.h $(INCL)/structs.h 

SRC =	exits.c map_line_checking.c sol_add_links_to_vertex.c \
		sol_data_saving.c sol_find_vertex_combo.c sol_logging.c \
		sol_queue_functions.c sol_search_for_path.c validation.c \
		fill.c print_functions.c sol_ant_queue_management.c \
		sol_data_saving_bonus.c sol_freeing_memory.c sol_option_colours.c \
		sol_releasing_ants.c sol_set_paths.c main.c read_data.c \
		sol_calculating_path_combo.c sol_distance_computing.c \
		sol_init_vertex.c sol_option_paths.c sol_removing_impasses.c \
		sol_sorting_links.c map_bonus.c read_options.c sol_create_ant_queue.c \
		sol_find_combos.c sol_links_manipulations.c sol_option_stat.c \
		sol_restoring_data.c sol_string_manipulations.c ants_lines_bonus.c

SRCSDIR = ./src/

SRCS = $(addprefix $(SRCSDIR), $(SRC))

OBJECTS_DIR = ./objects/

OBJECT_FILE = $(SRC:.c=.o)

OBJECTS = $(addprefix $(OBJECTS_DIR), $(OBJECT_FILE))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS_DIR) $(OBJECTS) 
	@make -C $(LIBF)
	$(CC) -L $(LIBF) -lft $(OBJECTS) -o $(NAME)

$(OBJECTS_DIR)%.o: $(SRCSDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCL) -I $(LIBF) -c $< -o $@

$(OBJECTS_DIR):
	@mkdir $(OBJECTS_DIR)

clean:
	@make -C $(LIBF) clean
	@/bin/rm -f $(OBJECTS)
	@/bin/rm -fr $(OBJECTS_DIR)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBF) fclean

re: fclean all

.PHONY: all, clean, fclean, re
