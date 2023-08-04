/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:48:36 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/30 22:05:27 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Rendering
 Your program has to represent the model in isometric projection.
 The coordinates of the landscape are stored in a .fdf file passed as a parameter
  to your program. Here is an example:
	$>cat 42.fdf
		0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		0  0  10 10 0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
		0  0  10 10 0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
		0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
		0  0  10 10 10 10 10 10 0  0  0  10 10 10 10 10 10 0  0
		0  0  10 10 10 10 10 10 0  0  0  10 10 10 10 10 10 0  0
		0  0  0  0  0  0  10 10 0  0  0  10 10 0  0  0  0  0  0
		0  0  0  0  0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
		0  0  0  0  0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
		0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

	Each number represents a point in space:
		• The horizontal position corresponds to its axis.
		• The vertical position corresponds to its ordinate.
		• The value corresponds to its altitude.
	Keep in mind that the goal of this project is not to parse maps! However,
	 this doesn’t mean that your program should crash when run. It means that
	  we assume the map contained in the file is properly formatted.

	Graphic management
• Your program has to display the image in a win.
• The management of your win must remain smooth (changing to another win, 
minimizing, and so forth).
• Pressing ESC must close the win and quit the program in a clean way.
• Clicking on the cross on the win’s frame must close the win and quit the 
program in a clean way.
• The use of the images of the MiniLibX is mandatory.
*/

#include "fdf.h"

//	Clear MLX struct.
static int	clear_mlx(t_mlx	*mlx)
{
	mlx_clear_window(mlx->id, mlx->win->id);
	mlx_destroy_window(mlx->id, mlx->win->id);
	mlx_destroy_image(mlx->id, mlx->img->id);
	mlx_destroy_display(mlx->id);
	free_mlx(mlx);
	exit(0);
}

static int	close_win(int keycode, void *param)
{
	if (keycode == 65307)
		clear_mlx(param);
	return (0);
}

// Create window and set hooks for 'x' close and ESC button exit, respectively.
static void	create_window(t_mlx *mlx)
{
	t_mlx_win	*win;

	win = mlx->win;
	win->id = mlx_new_window(mlx->id, WIN_X, WIN_Y, "FDF by bsilva-c");
	mlx_hook(win->id, 17, 1L << 17, clear_mlx, mlx);
	mlx_hook(win->id, 2, 1L << 0, close_win, mlx);
}

//	Check if files exists.
int	check_file(char *argv)
{
	int	fd;
	int	status;

	fd = open(argv, O_RDONLY);
	status = 0;
	if (read(fd, 0, 0) == -1)
		status = 1;
	close(fd);
	return (status);
}

/*
	1. Check if file exists.
	2. Read Map from file.
	3. Generate MLX Window.
	4. Generate Image with drawing.
	5. MLX_LOOP to keep window open and program running.
*/
int	main(int argc, char **argv)
{
	char		*file_ext;
	t_mlx		*mlx;

	if (argc == 2)
	{
		file_ext = ft_strchr(argv[1], '.');
		if (!ft_strncmp(file_ext, ".fdf", ft_strlen(file_ext)) \
			&& check_file(argv[1]) == 0)
		{
			mlx = generate_t_mlx(argv[1]);
			read_map(argv[1], mlx);
			mlx->id = mlx_init();
			create_window(mlx);
			create_image(mlx, argv[1]);
			mlx_loop(mlx->id);
			clear_mlx(mlx);
		}
	}
	return (0);
}
