/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by jpirsch           #+#    #+#             */
/*   Updated: 2015/04/04 09:32:33 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct			s_mat
{
	int					a;
	int					b;
	int					c;
	int					d;
	int					e;
	int					f;
	int					g;
	int					h;
	int					i;
	int					j;
	int					k;
	int					l;
	int					m;
	int					n;
	int					o;
	int					p;
}						t_mat;

typedef struct			s_key
{
	int					echap;
	int					decal_down;
	int					decal_up;
	int					decal_right;
	int					decal_left;
	int					zoom;
	int					zoom_back;
	int					cte1_increase;
	int					cte1_decrease;
	int					isometric;
	int					parallel;
	int					conic;
	int					scale_increase;
	int					scale_decrease;
	int					r;
	int					g;
	int					b;
}						t_key;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					size_line;
	int					depth;
	int					endian;
	int					**map;
	int					proj;
	double				scale;
	double				cte1;
	int					decalx;
	int					decaly;
	int					zoom;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	t_key				key;
}						t_env;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	unsigned int		color;
}						t_point;

/*
** hook
*/
void					init_t_key(t_key *key);
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);
int						loop_hook(t_env *e);
/*
** mlx_env
*/
void					px_to_img(t_env *e, int x, int y);
void					print_state(t_env *e);
void					env(int **map);
/*
** coord
*/
void					init_point(t_point *point, int x, int y, int z);
t_point					**malloc_grid(int **map);
t_point					**map_to_point(t_env *e);
/*
** drawline
*/
void					draw_grid(t_env *e, t_point **grid, int i, int j);
/*
** parse
*/
int						**parse(int fd);

#endif
