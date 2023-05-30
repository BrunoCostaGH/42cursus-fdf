/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:49:09 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/30 22:05:24 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_x_rows(char *argv)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (i);
}

int	count_y_cols(char *argv, int x)
{
	int		i;
	int		fd;
	char	*line;
	char	**content;

	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	content = 0;
	while (line && x > 0)
	{
		if (--x == 0)
		{
			content = ft_split(line, ' ');
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (content[i])
		free(content[i++]);
	free(content);
	free(line);
	close(fd);
	return (i);
}

static t_mlx_map	*set_map(t_mlx_map *map, char *line)
{
	int		i;
	int		x;
	char	**content;

	i = 0;
	x = 0;
	content = ft_split(line, ' ');
	while (content[i] && content[i][0] != '\n')
	{
		map->alt[x]->value = ft_atoi(content[i]) * 2.2;
		if (map->alt[x]->value > 0)
			map->alt[x]->color = 0xFF0000;
		else if (map->alt[x]->value == 0)
			map->alt[x]->color = 0xFFFFFF;
		else if (map->alt[x]->value < 0)
			map->alt[x]->color = 0x16A1E6;
		x++;
		free(content[i++]);
	}
	free(content);
	return (map);
}

//mlx->map[y]->alt[x]->(int)value
void	read_map(char *argv, t_mlx *mlx)
{
	int		y;
	int		fd;
	char	*line;

	y = 0;
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		mlx->map[y] = set_map(mlx->map[y], line);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	free(line);
	close(fd);
}
