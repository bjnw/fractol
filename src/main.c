/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 02:15:49 by ourgot            #+#    #+#             */
/*   Updated: 2020/07/28 02:15:49 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "fractol.h"
#include "libft.h"
#include "mlx.h"

static void	show_usage(const char *msg)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	panic("usage: ./fractol id[a]\n"
			"0 - mandelbrot\n"
			"1 - julia\n"
			"2 - buffalo\n"
			"3 - cosine mandelbrot\n"
			"4 - perpendicular mandelbrot\n"
			"5 - perpendicular celtic\n"
			"6 - tricorn\n"
			"7 - burning ship\n"
			"'a' is for ascii output\n");
}

static void	parse_arg(int argc, const char **argv,
				int *id, bool *ascii)
{
	if (argc != 2)
		show_usage("error: not enough arguments");
	if (ft_strlen(argv[1]) > 2)
		show_usage("error: invalid fractal id");
	*id = *argv[1] & ~060;
	if (*id < MANDELBROT || *id > BURNING_SHIP)
		show_usage("error: invalid fractal id");
	*ascii = false;
	if (ft_strlen(argv[1]) == 2)
	{
		if (argv[1][1] != 'a')
			show_usage("error: invalid ascii option");
		*ascii = true;
	}
}

int			main(int argc, const char **argv)
{
	t_context	ctx;
	t_fractal	fractal;
	int			id;
	bool		ascii;

	parse_arg(argc, argv, &id, &ascii);
	ft_memset(&ctx, 0, sizeof(t_context));
	ctx.fractal = &fractal;
	init_fractal(&fractal, id);
	if (ascii)
	{
		init_ascii_ctx(&ctx, &fractal);
		draw_ascii(&ctx);
	}
	else
	{
		init_mlx_ctx(&ctx, &fractal);
		draw_image(&ctx);
		mlx_loop(ctx.mlx);
	}
	return (EXIT_SUCCESS);
}
