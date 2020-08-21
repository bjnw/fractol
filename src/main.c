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

static void	show_usage(const char *msg)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	panic("usage: ./fractol <fractal_id>\n"
			"0 - mandelbrot\n"
			"1 - julia\n"
			"2 - buffalo\n"
			"3 - cosine mandelbrot\n"
			"4 - perpendicular mandelbrot\n"
			"5 - perpendicular celtic\n"
			"6 - burning ship\n"
			"7 - ascii mandelbrot\n");
}

static int	read_input(int argc, const char **argv)
{
	int id;

	if (argc != 2)
		show_usage("error: not enough arguments");
	if (ft_strlen(argv[1]) != 1)
		show_usage("error: invalid fractal id");
	id = *argv[1] & ~060;
	if (id < MANDELBROT || id > ASCII_MANDELBROT)
		show_usage("error: invalid fractal id");
	return (id);
}

static void	init_context(t_context *ctx, t_fractal *fractal)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		panic("error: mlx_init");
	ctx->win = mlx_new_window(ctx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	ctx->data = mlx_new_image(ctx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!ctx->data)
		panic("error: mlx_new_image");
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
	static const t_fractal	attrs[] = {
		{0, -2.5, 1.0, -1.5, 1.5, 0, 0, {0, 0}, 0, mandelbrot},
		{0, -2.2, 2.2, -1.8, 1.8, 0, 0, {JULIA_RE, JULIA_IM}, 0, julia},
		{0, -2.5, 1.0, -0.7, 2.1, 0, 0, {0, 0}, 0, buffalo},
		{0, -1.6, 1.1, -1.2, 1.2, 0, 0, {0, 0}, 0, cosine_mandelbrot},
		{0, -2.4, 1.6, -1.8, 1.8, 0, 0, {0, 0}, 0, perpendicular_mandelbrot},
		{0, -2.5, 1.0, -1.8, 1.8, 0, 0, {0, 0}, 0, perpendicular_celtic},
		{0, -2.6, 1.4, -1.0, 2.3, 0, 0, {0, 0}, 0, burning_ship}
	};

	*fractal = attrs[id];
	fractal->maxiter = ITER_DEFAULT;
	fractal->dx = (fractal->xmax - fractal->xmin) / WIN_WIDTH;
	fractal->dy = (fractal->ymax - fractal->ymin) / WIN_HEIGHT;
	fractal->cmap = fractal->iter == cosine_mandelbrot ?
		cmap_sepia : cmap_bernstein;
}

int			main(int argc, const char **argv)
{
	t_context	ctx;
	t_fractal	fractal;
	int			id;
	bool		ascii;

	id = read_input(argc, argv);
	if ((ascii = id == ASCII_MANDELBROT))
		id = 0;
	init_fractal(&fractal, id);
	if (ascii)
		draw_ascii(&fractal);
	else
	{
		init_context(&ctx, &fractal);
		draw_fractal(&ctx);
		mlx_loop(ctx.mlx);
	}
	return (EXIT_SUCCESS);
}
