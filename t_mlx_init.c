/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:59:06 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/30 22:04:13 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mlx_img	*generate_t_mlx_img(void)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (0);
	img->id = 0;
	img->buffer = 0;
	img->bpp = 0;
	img->size_line = 0;
	img->endian = 0;
	img->height = WIN_Y;
	img->width = WIN_X;
	return (img);
}

static t_mlx_win	*generate_t_mlx_win(void)
{
	t_mlx_win	*win;

	win = malloc(sizeof(t_mlx_win));
	if (!win)
		return (0);
	win->id = 0;
	return (win);
}

static t_map_alt	*generate_t_mlx_alt(void)
{
	t_map_alt	*alt;

	alt = malloc(sizeof(t_map_alt));
	if (!alt)
		return (0);
	alt->value = 0;
	alt->color = 0;
	return (alt);
}

static t_mlx_map	*generate_t_mlx_map(char *argv, int y)
{
	int			x;
	int			x_size;
	t_mlx_map	*map;

	x = 0;
	x_size = count_y_cols(argv, y);
	map = malloc(sizeof(t_mlx_map));
	if (!map)
		return (0);
	map->alt = ft_calloc(x_size + 1, sizeof(t_map_alt *));
	if (!map->alt)
		return (0);
	while (x < x_size)
	{
		map->alt[x] = generate_t_mlx_alt();
		x++;
	}
	return (map);
}

t_mlx	*generate_t_mlx(char *argv)
{
	int		x;
	int		y_size;
	t_mlx	*mlx;

	x = 0;
	y_size = count_x_rows(argv);
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (0);
	mlx->id = 0;
	mlx->zoom = 30;
	mlx->win = generate_t_mlx_win();
	mlx->img = generate_t_mlx_img();
	mlx->map = ft_calloc(y_size + 1, sizeof(t_mlx_map *));
	if (!mlx->map)
		return (0);
	while (x < y_size)
	{
		mlx->map[x] = generate_t_mlx_map(argv, x + 1);
		x++;
	}
	return (mlx);
}
