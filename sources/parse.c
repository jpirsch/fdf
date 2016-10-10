/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:44:11 by jpirsch           #+#    #+#             */
/*   Updated: 2015/04/04 08:53:41 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

char	**ft_split(char *line, int n)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**split;

	if (!(split = ft_tabmalloc(n + 2, 11)))
		return (NULL);
	i = 0;
	j = 0;
	l = (int)ft_strlen(line);
	while (i < l && j < n)
	{
		k = 0;
		while (i < l && ((line[i] >= '0' && line[i] <= '9') || line[i] == '-'))
		{
			split[j][k] = line[i];
			i++;
			k++;
		}
		while (i < l && !((line[i] >= '0' && line[i] <= '9')))
			i++;
		j++;
	}
	return (split);
}

int		*parse_line(char *line, int n)
{
	int		j;
	int		*map;
	char	**split;

	if (!line)
		return (NULL);
	split = ft_split(line, n);
	if (!(map = malloc(sizeof(int) * n + 2)))
		return (NULL);
	map[0] = n;
	j = 1;
	while (j <= n)
	{
		if (split[j - 1])
		{
			map[j] = ft_atoi(split[j - 1]);
		}
		j++;
	}
	while (j - 1 >= 0)
	{
		free(split[j - 1]);
		j--;
	}
	return (map);
}

int		**ft_realloc(int **map, int len)
{
	int		**newmap;
	int		size;
	int		i;

	if (!map)
		size = 2;
	else
		size = len + 1;
	if (!(newmap = malloc(sizeof(int *) * size)))
		return (NULL);
	if (!(newmap[0] = malloc(sizeof(int) * 1)))
		return (NULL);
	i = 1;
	if (map)
	{
		while (i < size)
		{
			newmap[i] = map[i];
			i++;
		}
	}
	newmap[0][0] = size;
	(map) ? free(map) : 1;
	return (newmap);
}

size_t	ft_countnumbers(const char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (((s[i] <= '9' && s[i] >= '0') || i == 0) &&
				(s[i + 1] > '9' || s[i + 1] < '0'))
			n++;
		i++;
	}
	return (n);
}

int		**parse(int fd)
{
	char	*line;
	int		**map;
	int		n;
	int		i;

	if (fd == -1)
		return (NULL);
	map = NULL;
	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		map = ft_realloc(map, i);
		n = ft_countnumbers(line);
		map[i] = parse_line(line, n);
		i++;
	}
	return (map);
}
