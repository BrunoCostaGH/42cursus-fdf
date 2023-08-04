/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_n_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:12:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/30 22:05:21 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Draw pixel.
void	pix(t_mlx *mlx, int x, int y, int color)
{
	char		*dst;
	t_mlx_img	*img;

	img = mlx->img;
	dst = img->buffer + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	if (DEV_MODE)
		mlx_pixel_put(mlx->id, mlx->win->id, x, y, color);
}

void	draw_line(t_mlx *mlx, t_point *p0, t_point *p1)
{
	double	s;
	t_point	*cur;

	cur = malloc(sizeof(t_point));
	if (!cur)
		exit(1);
	s = (float)(p1->y - p0->y) / (float)(p1->x - p0->x);
	if (s <= 1 && s >= -1)
		draw_line_r(mlx, p0, p1, cur);
	else
		draw_line_rr(mlx, p0, p1, cur);
	free(cur);
}

// calculate final coordinates
t_point	*set_coords(t_mlx *mlx, char *argv, int y0, int x0)
{
	int			x;
	int			y;
	int			z;
	t_point		*margin;
	t_point		*point;

	margin = malloc(sizeof(t_point));
	point = malloc(sizeof(t_point));
	if (!point || !margin)
		exit (1);
	margin->y = count_y_cols(argv, 1);
	margin->x = count_x_rows(argv);
	while ((y0 * mlx->zoom) > (WIN_X / 2) || (x0 * mlx->zoom) > (WIN_Y / 2))
		mlx->zoom--;
	x = x0 * mlx->zoom;
	y = y0 * mlx->zoom;
	z = mlx->map[y0]->alt[x0]->value;
	point->x = ((x - y) * cos(0.523599) + margin->x * mlx->zoom + mlx->zoom);
	point->y = (-z + (x + y) * sin(0.523599) + margin->y * mlx->zoom / 2);
	point->z = z;
	point->color = mlx->map[y0]->alt[x0]->color;
	free(margin);
	return (point);
}

// Initiate map draw.
void	draw_map(t_mlx	*mlx, char *argv)
{
	int		x;
	int		y;
	int		zoom;

	y = 0;
	zoom = mlx->zoom;
	while (mlx->map[y])
	{
		x = 0;
		if (zoom != mlx->zoom)
		{
			mlx_destroy_image(mlx->id, mlx->img->id);
			create_image(mlx, argv);
			return ;
		}
		if (draw_map_x(mlx, argv, y, x) == 1)
			return ;
		y++;
	}
}

// Create image and draw map.
void	create_image(t_mlx *mlx, char *argv)
{
	t_mlx_img	*img;

	img = mlx->img;
	img->id = mlx_new_image(mlx->id, WIN_X, WIN_Y);
	img->buffer = mlx_get_data_addr(img->id, &img->bpp, \
		&img->size_line, &img->endian);
	draw_map(mlx, argv);
	mlx_put_image_to_window(mlx->id, mlx->win->id, img->id, 0, 0);
}
