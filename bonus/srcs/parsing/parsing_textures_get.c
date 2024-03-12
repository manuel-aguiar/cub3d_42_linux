/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:22:48 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 20:22:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline int	get_texture_index_2(char *cmp)
{
	if (!ft_strncmp(cmp, "X_ENEMY", 8))
		return (X_ENEMY_TEX);
	if (!ft_strncmp(cmp, "Y_ENEMY", 8))
		return (Y_ENEMY_TEX);
	if (!ft_strncmp(cmp, "Z_ENEMY", 8))
		return (Z_ENEMY_TEX);
	if (!ft_strncmp(cmp, "MY_BULLET", 10))
		return (MY_BULLET_TEX);
	if (!ft_strncmp(cmp, "EN_BULLET", 10))
		return (EN_BULLET_TEX);
	if (!ft_strncmp(cmp, "WALL_BULLET", 12))
		return (WALL_BULLET_TEX);
	if (!ft_strncmp(cmp, "GUN", 4))
		return (GUN_TEX);
	if (!ft_strncmp(cmp, "DOOR", 5))
		return (DOOR_TEX);
	return (-1);
}

static int	get_texture_index(char *cmp)
{
	if (!ft_strncmp(cmp, "NO", 3))
		return (NO_TEX);
	if (!ft_strncmp(cmp, "SO", 3))
		return (SO_TEX);
	if (!ft_strncmp(cmp, "WE", 3))
		return (WE_TEX);
	if (!ft_strncmp(cmp, "EA", 3))
		return (EA_TEX);
	if (!ft_strncmp(cmp, "F", 2))
		return (F_TEX);
	if (!ft_strncmp(cmp, "C", 2))
		return (C_TEX);
	if (!ft_strncmp(cmp, "MEDI", 5))
		return (MEDI_TEX);
	if (!ft_strncmp(cmp, "AMMO", 5))
		return (AMMO_TEX);
	return (get_texture_index_2(cmp));
}

static inline int	extract_and_save(t_parsing *parsing)
{
	if (parsing->split_count != 2)
		return ((size_t)ft_free_charmat_null(&parsing->split, free));
	parsing->index_tex = get_texture_index(parsing->split[0]);
	if (parsing->index_tex == -1 \
	|| parsing->tex_data[parsing->index_tex].path)
		return ((size_t)ft_free_charmat_null(&parsing->split, free));
	parsing->tex_data[parsing->index_tex].path = parsing->split[1];
	parsing->split[1] = NULL;
	ft_free_charmat_null(&parsing->split, free);
	return (1);
}

int	separate_textures(t_parsing *parsing)
{
	if (parsing->list->len <= NUM_TEX)
		return (error_msg_int("cub3d: missing textures\n", 2, 0));
	parsing->nbr_tex = 0;
	while (parsing->nbr_tex < NUM_TEX)
	{
		if (!parsing->list->head)
			return (error_msg_int("cub3d: missing textures\n", 2, 0));
		parsing->split = ft_split_count(\
			(char *)(parsing->list->head->data), \
			"\t\v\n\r ", &parsing->split_count);
		if (!parsing->split)
			return (perror_msg_int("malloc", 0));
		if (!parsing->split_count)
			ft_free_charmat_null(&parsing->split, free);
		else
		{
			if (!extract_and_save(parsing))
				return (error_msg_int(\
				"cub3d: unknown/doubled input textures\n", 2, 0));
			parsing->nbr_tex++;
		}
		vdmlist_del_head(parsing->list, free);
	}
	return (1);
}
