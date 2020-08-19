/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
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

void	unload(int key, t_context *ctx)
{
	(void)key;
	(void)ctx;
	exit(EXIT_SUCCESS);
}

int		on_mousemove(int x, int y, t_context *ctx)
{
	if (ctx->fractal->iter != julia)
		return (0);
	ctx->fractal->k = (t_complex){
		JULIA_RE - (x * JULIA_RE) / WIN_WIDTH,
		JULIA_IM - (3 * y * JULIA_IM) / WIN_HEIGHT
	};
	draw_fractal(ctx);
	return (0);
}

int		on_mousedown(int button, int x, int y, t_context *ctx)
{
	int		i;
	double	z;

	if (button != MOUSE_SCROLL_UP && button != MOUSE_SCROLL_DOWN)
		return (0);
	i = button == MOUSE_SCROLL_UP ? 1 : -1;
	z = button == MOUSE_SCROLL_UP ? RATIO_MORE : RATIO_LESS;
	ctx->fractal->maxiter += i;
	zoom(ctx->fractal, z, x, y);
	draw_fractal(ctx);
	return (0);
}

void	set_fractal(int key, t_context *ctx)
{
	init_fractal(ctx->fractal, key - KEY_1);
}

void	set_iter(int key, t_context *ctx)
{
	if (key == KEY_0)
		ctx->fractal->maxiter = ITER_DEFAULT;
	else if (key == PLUS && ctx->fractal->maxiter < ITER_MAX)
		ctx->fractal->maxiter *= RATIO_MORE;
	else if (key == MINUS && ctx->fractal->maxiter > ITER_MIN)
		ctx->fractal->maxiter *= RATIO_LESS;
}

void	set_pan(int key, t_context *ctx)
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

void	set_cmap(int key, t_context *ctx)
{
	(void)key;
	ctx->fractal->cmap = ctx->fractal->cmap == color_sine ?
		color_bernstein : color_sine;
}

void	on_keydown(int key, t_context *ctx)
{
	t_handler				handler;
	static const t_handler	handlers[MAX_KEYS] = {
		[ESC] = unload,
		[KEY_1] = set_fractal,
		[KEY_2] = set_fractal,
		[KEY_3] = set_fractal,
		[KEY_4] = set_fractal,
		[KEY_5] = set_fractal,
		[KEY_6] = set_fractal,
		[KEY_0] = set_iter,
		[PLUS] = set_iter,
		[MINUS] = set_iter,
		[ARROW_UP] = set_pan,
		[ARROW_DOWN] = set_pan,
		[ARROW_LEFT] = set_pan,
		[ARROW_RIGHT] = set_pan,
		[C] = set_cmap
	};

	if (key <= MAX_KEYS && (handler = handlers[key]))
	{
		(*handler)(key, ctx);
		draw_fractal(ctx);
	}
}
