/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 05:56:28 by ourgot            #+#    #+#             */
/*   Updated: 2020/07/30 05:56:28 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fractol.h"
#include "keys.h"
#include "mlx.h"

void	change_fractal(int key, t_context *ctx)
{
	static int	id;
	static int	last;

	if (key == BRACKET_LEFT && id > MANDELBROT)
		id--;
	else if (key == BRACKET_RIGHT && id < SINE_MANDELBROT)
		id++;
	if (last != id)
	{
		last = id;
		init_fractal(ctx->fractal, id);
		init_dxdy(ctx, ctx->fractal);
	}
}

void	change_maxiter(int key, t_context *ctx)
{
	if (key == KEY_0)
		ctx->fractal->maxiter = ITER_DEFAULT;
	else if (key == PLUS && ctx->fractal->maxiter < ITER_MAX)
		ctx->fractal->maxiter *= RATIO_MORE;
	else if (key == MINUS && ctx->fractal->maxiter > ITER_MIN)
		ctx->fractal->maxiter *= RATIO_LESS;
}

void	change_pan(int key, t_context *ctx)
{
	if (key == ARROW_UP)
		pan(ctx->fractal, 0, -10);
	else if (key == ARROW_DOWN)
		pan(ctx->fractal, 0, 10);
	else if (key == ARROW_LEFT)
		pan(ctx->fractal, -10, 0);
	else if (key == ARROW_RIGHT)
		pan(ctx->fractal, 10, 0);
}

void	change_cmap(int key, t_context *ctx)
{
	static int			n;
	static const t_cmap	cmaps[] = {
		cmap_bernstein, cmap_sine, cmap_sepia, cmap_bw
	};

	(void)key;
	n = n < 3 ? n + 1 : 0;
	ctx->cmap = cmaps[n];
}
