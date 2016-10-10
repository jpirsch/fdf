/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:59:11 by jpirsch           #+#    #+#             */
/*   Updated: 2015/04/03 12:44:30 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"
#include "fdf.h"

void	init_point(t_point *point, int x, int y, int z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

t_point	**malloc_grid(int **map)
{
	t_point	**grid;
	int		i;

	if (!(grid = malloc(sizeof(t_point*) * map[0][0])))
		return (NULL);
	i = 0;
	while (i < map[0][0] - 1)
	{
		grid[i] = malloc(sizeof(t_point) * map[i + 1][0]);
		i++;
	}
	return (grid);
}

t_point	**map_to_point(t_env *e)
{
	t_point	**grid;
	int		i;
	int		j;

	i = 1;
	grid = malloc_grid(e->map);
	while (i < e->map[0][0])
	{
		j = 1;
		while (j < e->map[i][0])
		{
			init_point(&grid[i - 1][j - 1], (j * e->zoom) + e->decalx, (i * \
						e->zoom) + e->decaly, e->map[i][j]);
			j++;
		}
		i++;
	}
	return (grid);
}
