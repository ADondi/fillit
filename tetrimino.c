/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpripoae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 12:31:31 by mpripoae          #+#    #+#             */
/*   Updated: 2018/01/13 15:37:56 by mpripoae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Frees a list made with read_tetri.
*/

t_list		*free_list(t_list *list)
{
	t_etris	*tetris;
	t_list	*next;

	while (list)
	{
		tetris = (t_etris *)list->content;
		next = list->next;
		free_tetris(tetris);
		ft_memdel((void **)&list);
		list = next;
	}
	return (NULL);
}

/*
** Frees a tetrimino structure.
*/

void		free_tetris(t_etris *tetri)
{
	int y;

	y = 0;
	while (y < tetri->height)
	{
		ft_memdel((void **)(&(tetri->origin[y])));
		y++;
	}
	ft_memdel((void **)(&(tetri->origin)));
	ft_memdel((void **)&tetri);
}

/*
** Creates a new tetrimino structure.
*/

t_etris		*tetris_new(char **origin, int width, int height, char letter)
{
	t_etris		*tetris;

	tetris = ft_memalloc(sizeof(t_etris));
	tetris->origin = origin;
	tetris->width = width;
	tetris->height = height;
	tetris->letter = letter;
	return (tetris);
}

/*
** Creates a new point structure.
*/

t_point		*point_new(int x, int y)
{
	t_point		*point;

	point = ft_memalloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	return (point);
}
