/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:48:16 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/30 22:04:22 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_map(t_mlx_map **map)
{
	int	i[2];

	i[0] = 0;
	while (map[i[0]])
	{
		i[1] = 0;
		while (map[i[0]]->alt[i[1]])
			free(map[i[0]]->alt[i[1]++]);
		free(map[i[0]]->alt);
		free(map[i[0]++]);
	}
}

void	free_mlx(t_mlx *mlx)
{
	free_map(mlx->map);
	free(mlx->map);
	free(mlx->win);
	free(mlx->img);
	free(mlx->id);
	free(mlx);
}
