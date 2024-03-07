
## BUILD DETAILS

NAME 		=		cub3D

COMP 		= 		cc -O3  -g -fsanitize=address

FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
MLX_LIB		=		-Lminilibx-linux -L/usr/lib -lmlx -lXext -lX11 -lm -lz
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

## SOURCE FOLDERS

DIR_GAME			=	game
DIR_PARSING			=	parsing
DIR_GENERIC_UTILS 	= 	generic_utils
DIR_REN_LINUX		=	render_linux
DIR_COMPASS			=	compass
DIR_DRAWING_ALGOS	= 	drawing_algos
DIR_PLAYER			=	player
DIR_SPRITES			=	sprites
DIR_PIXEL_POINT		=	pixel_point
DIR_RAYCASTING		=	raycasting
DIR_HIT_DETECTION	=	hit_detection

## SOURCE FILES ##

INC_FILES		=		game.h				\
						sprites.h			\
						player.h			\
						vector.h			\
						parsing.h			\
						render_linux.h		\
						drawing_algos.h		\
						pixel_point.h		\
						compass.h			\
						generic_utils.h		\
						hit_detection.h

SRC_MAIN			=	main.c				\
						game_settings.h		\
						settings.c			\
						settings_template.c	\
						settings_template_enemy.c \
						settings_player.c

SRC_GAME			=	win_render_loop.c		\
						game_setup.c			\
						game_keys.c				\
						game_manager_keys.c		\
						game_manager_mouse.c	\
						game_rand_gen.c			\
						free_game.c				\
						game_rotate.c			\
						game_render.c			\
						game_load_textures.c	\
						render_inside_compass.c		\
						handle_collisions.c		\
						xpm_to_window.c				\
						game_render_hud.c			\
						bullet_rest.c				\
						bullet_start.c				\
						update_medi_ammo.c			\
						update_enemy_move.c			\
						update_bullet.c				\
						update_door.c


SRC_PLAYER			=	player_setup_and_actions.c	\
						player_aim.c				\
						player_move_1.c				\
						player_move_2.c				\
						player_crouch_prone.c		\
						player_walk_height.c		\
						player_rotate.c				\
						player_jump.c				\
						player_height_manager.c

SRC_PARSING			=	parsing_main.c						\
						parsing_textures_get.c				\
						parsing_textures_analise.c			\
						parsing_file_to_list.c				\
						parsing_print_utils.c				\
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

SRC_REN_WIN			=	win_init_window.c		\
						win_pixels.c			\
						win_callback_keys.c		\
						win_callback_mouse.c	\
						win_clock.c				\
						win_pause_blur_1.c		\
						win_pause_blur_2.c

SRC_REN_LINUX		=	linux_init_window.c		\
						linux_pixels.c			\
						linux_callback_keys.c		\
						linux_callback_mouse.c	\
						linux_clock.c				\
						linux_pause_manager.c		\
						linux_pause_blur_1.c		\
						linux_pause_blur_2.c		\
						linux_text_strings.c

SRC_COMPASS			=	compass_setup.c				\
						compass_render.c			\
						letter_north.c				\
						letter_south.c				\
						letter_east.c				\
						letter_west.c				\
						xlim_map_square.c			\
						xlim_map_square_helper.c	\
						xlim_inner_circle.c			\
						render_map_square.c			\
						render_ring.c				\
						render_ring_inner_pixels.c	\
						render_circle_player.c		\
						compass_blur.c				\
						compass_blur_passes.c

SRC_DRAWING_ALGOS	=	drawing_lines.c				\
						liang_barsky_clipping.c		\
						liang_barsky_utils.c		\
						xiaolinwu_antialiasing.c	\
						xiaolinwu_utils.c

SRC_PIXEL_POINT		=	gamma_correction.c				\
						pixels_1.c						\
						pixels_2.c						\
						translate_rotate.c

SRC_RAYCASTING		=	vec2d_utils1.c					\
						vec2d_utils2.c					\
						vec3d_utils1.c					\
						vec3d_utils2.c					\
						raycasting.c				\
						wallcast.c					\
						floorcast.c					\
						spritecast.c				\
						interpcast.c					\
						interpcast_setup.c			\
						interpcast_orientation.c			\
						shader.c					\
						tex_get_pixel.c

SRC_SPRITES			=	sprite_setup.c				\
						sprite_quicksort.c			\
						sprites_hitmap.c			\
						sprites_extract.c			\
						vertical_correction.c

SRC_HIT_DETECTION	=	lb_hit.c					\
						lb_hit_utils.c				\
						hit_list.c

## AGGREGATING FILES ##

INCS		:=		$(addprefix $(INC_PATH)/, $(INC_FILES))


SRCS 		:=		$(addprefix $(SRC_PATH)/, $(SRC_MAIN))											\
					$(addprefix $(SRC_PATH)/$(DIR_PARSING)/, $(SRC_PARSING)) 						\
					$(addprefix $(SRC_PATH)/$(DIR_GENERIC_UTILS)/, $(SRC_GENERIC_UTILS))			\
					$(addprefix $(SRC_PATH)/$(DIR_REN_LINUX)/, $(SRC_REN_LINUX))					\
					$(addprefix $(SRC_PATH)/$(DIR_COMPASS)/, $(SRC_COMPASS))						\
					$(addprefix $(SRC_PATH)/$(DIR_DRAWING_ALGOS)/, $(SRC_DRAWING_ALGOS))			\
					$(addprefix $(SRC_PATH)/$(DIR_GAME)/, $(SRC_GAME))								\
					$(addprefix $(SRC_PATH)/$(DIR_PLAYER)/, $(SRC_PLAYER))							\
					$(addprefix $(SRC_PATH)/$(DIR_RAYCASTING)/, $(SRC_RAYCASTING))					\
					$(addprefix $(SRC_PATH)/$(DIR_PIXEL_POINT)/, $(SRC_PIXEL_POINT))				\
					$(addprefix $(SRC_PATH)/$(DIR_SPRITES)/, $(SRC_SPRITES))						\
					$(addprefix $(SRC_PATH)/$(DIR_HIT_DETECTION)/, $(SRC_HIT_DETECTION))



OBJS 		:=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

ALL_INCS	= 		-I$(INC_PATH) -I$(LIB_PATH)/$(LIB_INC_P) $(INC_MLX)
LIBS		=		$(ADD_LIB) $(LIB_PATH)/$(LIBFT) $(MLX_LIB)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) $(ALL_INCS) -o $(NAME) $(LIBS)
	@echo Program $(NAME) ready!!

$(OBJ_PATH)/settings.o : $(SRC_PATH)/settings.c $(SRC_PATH)/game_settings.h
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

$(OBJ_PATH)/settings_template.o : $(SRC_PATH)/settings_template.c $(SRC_PATH)/game_settings.h
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

$(OBJ_PATH)/settings_player.o : $(SRC_PATH)/settings_player.c $(SRC_PATH)/game_settings.h
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	mkdir -p $(dir $@)
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIB_PATH)
##	@$(MAKE) -C $(MLX_PATH)

$(MLX):
	@$(MAKE) -C $(MLX_PATH)

message:
	@echo Building program....

clean:
	@echo Removing object files.....
	@if [ -d "$(OBJ_PATH)" ]; then \
        rm -rf $(OBJ_PATH); \
    fi
	@$(MAKE) clean -C $(LIB_PATH)
##	@$(MAKE) clean -C $(MLX_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	@if [ -n "$(wildcard  $(NAME))" ]; then \
        $(RM) $(NAME); \
    fi
	@if [ -n "$(wildcard  $(LIB_PATH)/$(LIBFT))" ]; then \
        $(RM) $(LIB_PATH)/$(LIBFT); \
    fi
	@echo Done!!

re: fclean all

run: $(NAME)
	@./$(NAME)

git: fclean
	git add * && git commit -m "commiting" && git push

.PHONY: clean fclean message bonus
