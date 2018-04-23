/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpripoae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 12:31:07 by mpripoae          #+#    #+#             */
/*   Updated: 2018/01/13 15:37:50 by mpripoae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Backtracking implementation of the solver.
** solve_map :: Map -> Bool
*/

int		solve_map(t_map *map, t_list *list)
{
	CREATE_VAR;
	if (list == NULL)
		return (1);
	y = 0;
	tetri = (t_etris *)(list->content);
	while (y < map->size - tetri->height + 1)
	{
		x = 0;
		while (x < map->size - tetri->width + 1)
		{
			point = point_new(x, y);
			if (can_place(tetri, map, point))
			{
				set_piece(tetri, map, point, tetri->letter);
				if (solve_map(map, list->next))
					return (1);
				else
					set_piece(tetri, map, point_new(x, y), '.');
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
** Tries to solve maps starting from the smallest possible size.
** solve :: [Tetris] -> Map
*/

t_map	*solve(t_list *list)
{
	t_map	*map;
	int		size;

	size = ft_sqrt_up(ft_lstcount(list) * 4);
	map = map_new(size);
	while (!solve_map(map, list))
	{
		size++;
		free_map(map);
		map = map_new(size);
	}
	return (map);
}
