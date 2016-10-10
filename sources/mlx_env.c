/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by jpirsch           #+#    #+#             */
/*   Updated: 2015/04/04 09:43:28 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

void	px_to_img(t_env *e, int x, int y)
{
	e->data[y * e->size_line + x * 4 + 2] = e->r;
	e->data[y * e->size_line + x * 4 + 1] = e->g;
	e->data[y * e->size_line + x * 4] = e->b;
}

void	string_put(char *s1, char *s2, t_env *e, int y)
{
	char *str;

	str = ft_strnew(60);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	mlx_string_put(e->mlx, e->win, 1200, y, 0xFFFF00, str);
}

void	print_state(t_env *e)
{
	char	*str;

	string_put("Zoom : ", ft_itoa(e->zoom), e, 50);
	(e->proj == 0) ? str = ft_strdup("isometric") : (void)e->proj;
	(e->proj == 1) ? str = ft_strdup("parallel") : (void)e->proj;
	(e->proj == 2) ? str = ft_strdup("conic") : (void)e->proj;
	string_put("Projection : ", str, e, 60);
	ft_strdel(&str);
	string_put("Offset X : ", ft_itoa(e->decalx), e, 70);
	string_put("Offset Y : ", ft_itoa(e->decaly), e, 80);
	str = ft_strnew(20);
	str = ft_strcat(str, " R = ");
	str = ft_strcat(str, ft_itoa((int)e->r));
	str = ft_strcat(str, " G = ");
	str = ft_strcat(str, ft_itoa((int)e->g));
	str = ft_strcat(str, " B = ");
	str = ft_strcat(str, ft_itoa((int)e->b));
	string_put(str, "", e, 90);
	ft_strdel(&str);
}

void	env(int **map)
{
	t_env	e;

	e.map = map;
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, 1440, 900, "sandwich");
	e.img = mlx_new_image(e.mlx, 1440, 900);
	e.data = mlx_get_data_addr(e.img, &e.depth, &e.size_line, &e.endian);
	e.proj = 0;
	e.scale = 2.5;
	e.cte1 = 0.6;
	e.zoom = 8;
	e.decalx = 150;
	e.decaly = 150;
	e.r = 255;
	e.g = 0;
	e.b = 0;
	init_t_key(&e.key);
	draw_grid(&e, NULL, 0, 0);
	mlx_hook(e.win, 2, 1, key_press, &e);
	mlx_hook(e.win, 3, 2, key_release, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
}
