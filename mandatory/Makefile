
## BUILD DETAILS

NAME 		=		cub3D

COMP 		= 		cc -O3  ##-g -fsanitize=address

FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
ADD_MLX		=		-L./$(MLX_PATH) -lmlx -Lminilibx-linux
X11_LIB		=		-L/usr/lib -lXext -lX11 -lm -lz
RM 			=		rm
MAKE		=		make


## FOLDER PATH ##
INC_MLX 	=		-I/usr/include -Iminilibx-linux
MLX_PATH	=		minilibx-linux
INC_PATH	=		incs
SRC_PATH	=		srcs
OBJ_PATH	=		objs

LIB_PATH	=		libft
LIB_INC_P	=		incs


## SOURCE LIBRARIES
LIBFT		=		libft.a
MLX			=		mlx.a

## SOURCE FOLDERS

DIR_GAME			=	game
DIR_PARSING			=	parsing
DIR_GENERIC_UTILS 	= 	generic_utils
DIR_REN_LINUX		=	render_linux
DIR_DRAWING_ALGOS	= 	drawing_algos
DIR_PLAYER			=	player
DIR_PIXEL_POINT		=	pixel_point
DIR_RAYCASTING		=	raycasting

## SOURCE FILES ##

INC_FILES		=		game.h				\
						player.h			\
						vector.h			\
						parsing.h			\
						render_linux.h		\
						drawing_algos.h		\
						pixel_point.h		\
						generic_utils.h

SRC_MAIN			=	main.c				\
						settings.c			\
						settings_player.c

SRC_GAME			=	win_render_loop.c			\
						game_setup.c				\
						game_manager_keys.c			\
						free_game.c					\
						game_rotate.c				\
						game_render.c				\
						game_load_textures.c		\
						game_updates.c				\
						map_collisions.c			\
						map_collision_corners.c	


SRC_PLAYER			=	player_setup_and_actions.c	\
						player_move_1.c				\
						player_move_2.c				\
						player_rotate.c				

SRC_PARSING			=	parsing_main.c						\
						parsing_textures_get.c				\
						parsing_textures_analise.c			\
						parsing_file_to_list.c				\
						map_flood_count.c					\
						map_funcs.c							\
						map_dimensions.c

SRC_GENERIC_UTILS 	= 	ft_split_count_replenish.c		\
						clamp.c							\
						fpow_2.c						\
						ft_fabs.c						\
						radian_truncate.c				\
						cubed_string_funcs.c			\
						ft_ternary.c					\
						ft_swap.c						\
						float_equal.c

SRC_REN_LINUX		=	linux_init_window.c		\
						linux_pixels.c			\
						linux_callback_keys.c		\
						linux_callback_mouse.c	\
						linux_xpm_to_window.c

SRC_DRAWING_ALGOS	=	drawing_lines.c				\
						liang_barsky_clipping.c		\
						liang_barsky_utils.c		\
						xiaolinwu_antialiasing.c	\
						xiaolinwu_utils.c

SRC_PIXEL_POINT		=	gamma_correction.c				\
						pixels_1.c						\
						pixels_2.c						

SRC_RAYCASTING		=	vec2d_utils1.c					\
						vec2d_utils2.c					\
						vec3d_utils1.c					\
						vec3d_utils2.c					\
						raycasting.c				\
						wallcast.c					\
						floorcast.c					\
						ceilcast.c					\
						tex_get_pixel.c

## AGGREGATING FILES ##

INCS		:=		$(addprefix $(INC_PATH)/, $(INC_FILES))


SRCS 		:=		$(addprefix $(SRC_PATH)/, $(SRC_MAIN))											\
					$(addprefix $(SRC_PATH)/$(DIR_PARSING)/, $(SRC_PARSING)) 						\
					$(addprefix $(SRC_PATH)/$(DIR_GENERIC_UTILS)/, $(SRC_GENERIC_UTILS))			\
					$(addprefix $(SRC_PATH)/$(DIR_REN_LINUX)/, $(SRC_REN_LINUX))					\
					$(addprefix $(SRC_PATH)/$(DIR_DRAWING_ALGOS)/, $(SRC_DRAWING_ALGOS))			\
					$(addprefix $(SRC_PATH)/$(DIR_GAME)/, $(SRC_GAME))								\
					$(addprefix $(SRC_PATH)/$(DIR_PLAYER)/, $(SRC_PLAYER))							\
					$(addprefix $(SRC_PATH)/$(DIR_RAYCASTING)/, $(SRC_RAYCASTING))					\
					$(addprefix $(SRC_PATH)/$(DIR_PIXEL_POINT)/, $(SRC_PIXEL_POINT))				



OBJS 		:=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

ALL_INCS	= 		-I$(INC_PATH) -I$(LIB_PATH)/$(LIB_INC_P) $(INC_MLX)
LIBS		=		$(ADD_LIB) $(ADD_MLX) $(X11_LIB)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_PATH)
	$(MAKE) -C $(MLX_PATH)
	$(COMP) $(FLAGS) $(OBJS) $(ALL_INCS) $(LIBS) -o $@

$(OBJ_PATH)/settings.o : $(SRC_PATH)/settings.c $(SRC_PATH)/game_settings.h
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

$(OBJ_PATH)/settings_player.o : $(SRC_PATH)/settings_player.c $(SRC_PATH)/game_settings.h
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

message:
	@echo Building program....

clean:
	@echo Removing object files.....
	if [ -d "$(OBJ_PATH)" ]; then \
        rm -rf $(OBJ_PATH); \
    fi
	$(MAKE) clean -C $(LIB_PATH)
	$(MAKE) clean -C $(MLX_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	@if [ -n "$(wildcard  $(NAME))" ]; then \
        $(RM) $(NAME); \
    fi
	@if [ -n "$(wildcard  $(LIB_PATH)/$(LIBFT))" ]; then \
        $(RM) $(LIB_PATH)/$(LIBFT); \
    fi
	@if [ -n "$(wildcard  $(MLX_PATH)/$(MLX))" ]; then \
        $(RM) $(MLX_PATH)/$(MLX); \
    fi
	@echo Done!!

re: fclean all

run: $(NAME)
	@./$(NAME)

git: fclean
	git add * && git commit -m "commiting" && git push

.PHONY: clean fclean message bonus
