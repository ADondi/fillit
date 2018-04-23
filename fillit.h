/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpripoae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 12:29:25 by mpripoae          #+#    #+#             */
/*   Updated: 2018/01/13 15:27:24 by mpripoae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# define CREATE_VAR int x; int y; t_etris *tetri; t_point *point;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_etris
{
	char		**origin;
	int			width;
	int			height;
	char		letter;
}				t_etris;

typedef struct	s_map
{
	int			size;
	char		**array;
}				t_map;

/*
** READER
*/

t_list			*read_tetri(int fd);
int				check_counts(char *str, int count);
int				check_connection(char *str);
t_etris			*get_piece(char *str, char value);
void			min_max(char *str, t_point *min, t_point *max);
t_list			extra_check(char *buf, int count, t_etris *tetris, t_list *list);


/*
** MAP STRUCTURE
*/

void			free_map(t_map *map);
void			print_map(t_map *map);
t_map			*map_new(int size);
int				can_place(t_etris *tetri, t_map *map, t_point *point);
void			set_piece(t_etris *tetri, t_map *map, t_point *point, char c);

/*
** TETRIMINO STRUCTURE
*/

t_list			*free_list(t_list *list);
void			free_tetris(t_etris *tetri);
t_etris			*tetris_new(char **pos, int width, int height, char c);
t_point			*point_new(int x, int y);

/*
** SOLVER
*/

int				solve_map(t_map *map, t_list *list);
t_map			*solve(t_list *list);

#endif
