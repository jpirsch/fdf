/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2015/04/04 09:53:09 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"

void	putl(t_env *e, t_point start, t_point end)
{
	double	dd;
	double	x;
	double	y;
	double	dx;
	double	dy;

	x = start.x;
	y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	dd = sqrt((dx * dx) + (dy * dy));
	dx = dx / dd;
	dy = dy / dd;
	while (dd-- >= 0)
	{
		if (x < 1440 && x > 0 && y > 0 && y < 900)
			px_to_img(e, ABS(x), ABS(y));
		x += dx;
		y += dy;
	}
}

t_point	**isometric(t_point **grid, t_env *e)
{
	int		i;
	int		j;
	double	cte2;

	i = 0;
	cte2 = e->cte1 + (e->cte1 / 2);
	while (i < e->map[0][0] - 1)
	{
		j = 0;
		while (j < e->map[i + 1][0] - 1)
		{
			if (grid[i][j].z != 0)
				grid[i][j].z *= e->scale;
			grid[i][j].x -= e->cte1 * grid[i][j].x - cte2 * grid[i][j].y;
			grid[i][j].y -= grid[i][j].z + e->cte1 / 2 * grid[i][j].x + \
							cte2 / 2 * grid[i][j].y;
			j++;
		}
		i++;
	}
	return (grid);
}

t_point	**parallel(t_point **grid, t_env *e)
{
	int		i;
	int		j;

	i = 0;
	while (i < e->map[0][0] - 1)
	{
		j = 1;
		while (j < e->map[i + 1][0] - 1)
		{
			if (grid[i][j].z != 0)
				grid[i][j].z *= e->scale;
			grid[i][j].x -= 0.7 * grid[i][j].z;
			grid[i][j].y -= (0.7 / 2) * grid[i][j].z;
			j++;
		}
		i++;
	}
	return (grid);
}

void	draw_grid(t_env *e, t_point **grid, int i, int j)
{
	grid = map_to_point(e);
	grid = (e->proj == 0) ? isometric(grid, e) : parallel(grid, e);
	i = 0;
	while ((i + 1) < e->map[0][0] - 1)
	{
		j = 0;
		while ((j + 1) < e->map[i + 1][0] - 1)
		{
			(grid[i][j + 1].x) ? putl(e, grid[i][j], grid[i][j + 1]) : 1;
			(grid[i + 1][j].x) ? putl(e, grid[i][j], grid[i + 1][j]) : 1;
			if (j + 1 == e->map[i + 1][0] - 2
				&& e->map[i + 1][0] <= e->map[i + 2][0])
				putl(e, grid[i][j + 1], grid[i + 1][j + 1]);
			if (i + 1 == e->map[0][0] - 2)
				putl(e, grid[i + 1][j], grid[i + 1][j + 1]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);
}
