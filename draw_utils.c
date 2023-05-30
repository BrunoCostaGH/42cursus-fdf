/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:08:17 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/30 22:05:09 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Draw regular slope
void	draw_line_r(t_mlx *mlx, t_point *p0, t_point *p1, t_point *cur)
{
	double	s;
	double	step;

	s = (float)(p1->y - p0->y) / (float)(p1->x - p0->x);
	step = p1->y - s * p1->x;
	*cur = *p0;
	if (p0->x <= p1->x)
	{
		while (cur->x <= p1->x)
		{
			pix(mlx, cur->x, round(s * cur->x + step), getcolor(p0, cur, p1));
			cur->x++;
		}
	}
	else if (p0->x > p1->x)
	{
		while (cur->x >= p1->x)
		{
			pix(mlx, cur->x, round(s * cur->x + step), getcolor(p0, cur, p1));
			cur->x--;
		}
	}
}

// Draw reverse slope
void	draw_line_rr(t_mlx *mlx, t_point *p0, t_point *p1, t_point *cur)
{
	double	s;
	double	step;

	s = (float)(p1->y - p0->y) / (float)(p1->x - p0->x);
	step = p1->y - s * p1->x;
	*cur = *p0;
	if (p0->y <= p1->y)
	{
		while (cur->y <= p1->y)
		{
			pix(mlx, round((cur->y - step) / s), cur->y, getcolor(p0, cur, p1));
			cur->y++;
		}
	}
	else if (p0->y > p1->y)
	{
		while (cur->y >= p1->y)
		{
			pix(mlx, round((cur->y - step) / s), cur->y, getcolor(p0, cur, p1));
			cur->y--;
		}
	}
}

int	draw_map_x(t_mlx *mlx, char *argv, int y, int x)
{
	t_point	*p0;
	t_point	*p1;

	while (mlx->map[y]->alt[x])
	{
		if (y > 0)
		{
			p0 = set_coords(mlx, argv, y - 1, x);
			p1 = set_coords(mlx, argv, y, x);
			draw_line(mlx, p0, p1);
			free(p0);
			p0 = 0;
			free(p1);
			p1 = 0;
		}
		x++;
	}
	while (--x)
		draw_map_y(mlx, argv, y, x);
	return (0);
}

int	draw_map_y(t_mlx *mlx, char *argv, int y, int x)
{
	t_point	*p0;
	t_point	*p1;

	p0 = set_coords(mlx, argv, y, x - 1);
	p1 = set_coords(mlx, argv, y, x);
	draw_line(mlx, p0, p1);
	free(p0);
	p0 = 0;
	free(p1);
	p1 = 0;
	return (0);
}
