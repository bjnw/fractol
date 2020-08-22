/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 02:15:49 by ourgot            #+#    #+#             */
/*   Updated: 2020/07/28 02:15:49 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

#include "fractol.h"
#include "keys.h"
#include "libft.h"
#include "mlx.h"

#define RATIO_ASCII	3.8

static int	get_termwidth(void)
{
	struct winsize win;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	return (win.ws_col);
}

void		init_fractal(t_fractal *fractal, int id)
{
	static const t_fractal attrs[] = {
		{0, -2.5, 1.0, -1.5, 1.5, 0, 0, {0, 0}, mandelbrot},
		{0, -2.2, 2.2, -1.8, 1.8, 0, 0, {JULIA_RE, JULIA_IM}, julia},
		{0, -2.5, 1.0, -0.7, 2.1, 0, 0, {0, 0}, buffalo},
		{0, -1.6, 1.1, -1.2, 1.2, 0, 0, {0, 0}, cosine_mandelbrot},
		{0, -2.4, 1.6, -1.8, 1.8, 0, 0, {0, 0}, perpendicular_mandelbrot},
		{0, -2.5, 1.0, -1.8, 1.8, 0, 0, {0, 0}, perpendicular_celtic},
		{0, -2.6, 1.4, -1.0, 2.3, 0, 0, {0, 0}, burning_ship}
	};

	*fractal = attrs[id];
	fractal->maxiter = ITER_DEFAULT;
}

void	init_mlx_ctx(t_context *ctx, t_fractal *fractal)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		panic("error: mlx_init");
	ctx->win = mlx_new_window(ctx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	ctx->img = mlx_new_image(ctx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!ctx->img)
		panic("error: mlx_new_image");
	ctx->addr =
		mlx_get_data_addr(ctx->img, &ctx->bpp, &ctx->linesize, &ctx->endian);
	mlx_hook(ctx->win, DESTROY_NOTIFY, 0, (int (*)())unload, ctx);
	mlx_hook(ctx->win, KEY_DOWN, 1, (int (*)())on_keydown, ctx);
	mlx_hook(ctx->win, MOUSE_DOWN, 1 << 2, on_mousedown, ctx);
	mlx_hook(ctx->win, MOUSE_MOVE, 1 << 8, on_mousemove, ctx);
	ctx->width = WIN_WIDTH;
	ctx->height = WIN_HEIGHT;
	ctx->plot = plot_image;
	ctx->cmap = fractal->iter == cosine_mandelbrot ?
		cmap_sepia : cmap_bernstein;
	fractal->dx = (fractal->xmax - fractal->xmin) / (WIN_WIDTH - 1);
	fractal->dy = (fractal->ymax - fractal->ymin) / (WIN_HEIGHT - 1);
}

void	init_ascii_ctx(t_context *ctx, t_fractal *fractal)
{
	const int		width = get_termwidth();
	const int		height = width / RATIO_ASCII;
	const size_t	size = width * height;

	ctx->img = xmalloc(size);
	ctx->width = width;
	ctx->height = height;
	ctx->plot = plot_ascii;
	ctx->cmap = cmap_ascii;
	fractal->dx = (fractal->xmax - fractal->xmin) / (width - 1);
	fractal->dy = (fractal->ymax - fractal->ymin) / (height - 1);
}
