/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:36:12 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/01/18 14:13:22 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

double	percent(int start, int end, int cur)
{
	double	location;
	double	width;

	width = (end - start);
	location = (cur - start);
	if (width == 0)
		return (0);
	else
		return (location / width);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	getcolor(t_point *start, t_point *cur, t_point *end)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;
	t_point	*delta;

	if (cur->color == end->color)
		return (cur->color);
	delta = malloc(sizeof(t_point));
	if (!delta)
		exit(1);
	delta->x = ft_abs(end->x - start->x);
	delta->y = ft_abs(end->y - start->y);
	if (delta->x > delta->y)
		percentage = percent(start->x, end->x, cur->x);
	else
		percentage = percent(start->y, end->y, cur->y);
	red = get_light((start->color >> 16) & 0xFF, \
		(end->color >> 16) & 0xFF, percentage);
	green = get_light((start->color >> 8) & 0xFF, \
		(end->color >> 8) & 0xFF, percentage);
	blue = get_light(start->color & 0xFF, end->color & 0xFF, percentage);
	free(delta);
	return ((red << 16) | (green << 8) | blue);
}
