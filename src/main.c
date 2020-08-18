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
#include "keys.h"
#include "libft.h"
#include "mlx.h"

// [ ] menu

static void	show_usage(const char *msg)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	panic("usage: ./fractol <fractal_id>\n"
			"0 - mandelbrot\n"
			"1 - julia\n"
			"2 - buffalo\n"
			"3 - perpendicular celtic\n"
			"4 - perpendicular mandelbrot\n"
			"5 - burning ship\n");
}

static int	read_input(int argc, const char **argv)
{
	int id;

	if (argc != 2)
		show_usage("error: not enough arguments");
	if (ft_strlen(argv[1]) != 1)
		show_usage("error: invalid fractal id");
	id = *argv[1];
	if (id < '0' || id > '5')
		show_usage("error: invalid fractal id");
	return (id & ~060);
}

static void	init_context(t_context *ctx, t_fractal *fractal)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->mlx = mlx_init();
	ctx->win = mlx_new_window(ctx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	ctx->data = mlx_new_image(ctx->mlx, WIN_WIDTH, WIN_HEIGHT);
	ctx->addr = mlx_get_data_addr(ctx->data, &ctx->bpp,
			&ctx->linesize, &ctx->endian);
	ctx->fractal = fractal;
	mlx_hook(ctx->win, DESTROY_NOTIFY, 0, (int (*)())unload, ctx);
	mlx_hook(ctx->win, KEY_DOWN, 1, (int (*)())on_keydown, ctx);
	mlx_hook(ctx->win, MOUSE_DOWN, 1 << 2, on_mousedown, ctx);
	mlx_hook(ctx->win, MOUSE_MOVE, 1 << 8, on_mousemove, ctx);
}

void		init_fractal(t_fractal *fractal, int id)
{
	static const t_fractal	params[] = {
		{0, 0, -2.5, 1.0, -1.5, 1.5, 0, 0, {0, 0}, 0, mandelbrot},
		{0, 0, -2.2, 2.2, -1.8, 1.8, 0, 0, {JULIA_RE, JULIA_IM}, 0, julia},
		{0, 0, -2.5, 1.0, -0.7, 2.1, 0, 0, {0, 0}, 0, buffalo},
		{0, 0, -2.5, 1.0, -1.8, 1.8, 0, 0, {0, 0}, 0, perpendicular_celtic},
		{0, 0, -2.4, 1.6, -1.8, 1.8, 0, 0, {0, 0}, 0, perpendicular_mandelbrot},
		{0, 0, -2.6, 1.4, -1.0, 2.3, 0, 0, {0, 0}, 0, burning_ship}
	};

	*fractal = params[id];
	fractal->maxiter = ITER_INIT;
	fractal->bailout = BAILOUT_INIT;
	fractal->dx = (fractal->xmax - fractal->xmin) / (WIN_WIDTH - 1);
	fractal->dy = (fractal->ymax - fractal->ymin) / (WIN_HEIGHT - 1);
	fractal->cmap = color_bernstein;
}

int			main(int argc, const char **argv)
{
	t_context	ctx;
	t_fractal	fractal;
	int			id;

	id = read_input(argc, argv);
	init_fractal(&fractal, id);
	init_context(&ctx, &fractal);
	draw_fractal(&ctx);
	mlx_loop(ctx.mlx);
	return (EXIT_SUCCESS);
}
