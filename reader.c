/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpripoae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:32:14 by mpripoae          #+#    #+#             */
/*   Updated: 2018/01/13 15:37:40 by mpripoae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Read tetriminos from fd and put them in a list.
** Read 21 chars at a time
** read_tetri :: Handle -> [Tetris]
*/

t_list	*read_tetri(int fd)
{
	char	*buf;
	int		count;
	t_list	*list;
	t_etris	*tetris;
	char	letter;

	buf = ft_strnew(21);
	list = NULL;
	letter = 'A';
	while ((count = read(fd, buf, 21)) >= 20)
	{
		tetris = get_piece(buf, letter++);
		if (check_counts(buf, count) != 0 || tetris == NULL)
		{
			ft_memdel((void **)&buf);
			return (free_list(list));
		}
		ft_lstadd(&list, ft_lstnew(tetris, sizeof(t_etris)));
		ft_memdel((void **)&tetris);
	}
	ft_memdel((void **)&buf);
	if (count != 0)
		return (free_list(list));
	ft_lstrev(&list);
	return (list);
}

/*
** Checks character counts and that chunk format is valid.
** 0 - no errors
** 1 - invalid CHAR
** 2 - more than 4 blocs
** 3 - 5th  char is not eol
** 4 - last char is not eol
** 5 - connetion is not good
** check_counts :: String -> Int -> Bool
*/

int		check_counts(char *str, int count)
{
	int i;
	int blocs;

	blocs = 0;
	i = 0;
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (!(str[i] == '#' || str[i] == '.'))
				return (1);
			if (str[i] == '#' && ++blocs > 4)
				return (2);
		}
		else if (str[i] != '\n')
			return (3);
		i++;
	}
	if (count == 21 && str[20] != '\n')
		return (4);
	if (!check_connection(str))
		return (5);
	return (0);
}

/*
** Checks for 6 or 8 connection counts.
** check_connection :: String -> Bool
*/

int		check_connection(char *str)
{
	int block;
	int i;

	block = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				block++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				block++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				block++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				block++;
		}
		i++;
	}
	return (block == 6 || block == 8);
}

/*
** Reads a piece from a valid chunk, allocates a structure and populates it.
** get_piece :: String -> Char -> Tetris
*/

t_etris	*get_piece(char *str, char letter)
{
	t_point		*min;
	t_point		*max;
	char		**origin;
	int			i;
	t_etris		*tetri;

	min = point_new(3, 3);
	max = point_new(0, 0);
	min_max(str, min, max);
	origin = ft_memalloc(sizeof(char *) * (max->y - min->y + 1));
	i = 0;
	while (i < max->y - min->y + 1)
	{
		origin[i] = ft_strnew(max->x - min->x + 1);
		ft_strncpy(origin[i], str + (min->x) + (i + min->y) * 5,
					max->x - min->x + 1);
		i++;
	}
	tetri = tetris_new(origin, max->x - min->x + 1,
			max->y - min->y + 1, letter);
	ft_memdel((void **)&min);
	ft_memdel((void **)&max);
	return (tetri);
}

/*
** Utility function to get min-max values for get_piece.
** min_max :: String -> Point -> Point -> (Point, Point)
*/

void	min_max(char *str, t_point *min, t_point *max)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i / 5 < min->y)
				min->y = i / 5;
			if (i / 5 > max->y)
				max->y = i / 5;
			if (i % 5 < min->x)
				min->x = i % 5;
			if (i % 5 > max->x)
				max->x = i % 5;
		}
		i++;
	}
}
