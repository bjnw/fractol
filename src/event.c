/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 05:56:28 by ourgot            #+#    #+#             */
/*   Updated: 2020/07/30 05:56:28 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "fractol.h"
#include "keys.h"
#include "mlx.h"

int		on_mousemove(int x, int y, t_context *ctx)
{
	if (ctx->fractal->iter != julia)
		return (0);
	ctx->fractal->k = (t_complex){
		JULIA_RE - (M_PI_2 * x * JULIA_RE) / WIN_WIDTH,
		JULIA_IM - (M_PI * y * JULIA_IM) / WIN_HEIGHT
	};
	draw_image(ctx);
	return (0);
}

int		on_mousedown(int button, int x, int y, t_context *ctx)
{
	if (button == MOUSE_SCROLL_UP)
	{
		if (ctx->fractal->maxiter < ITER_MAX)
			ctx->fractal->maxiter += ITER_DELTA;
		zoom(ctx->fractal, RATIO_MORE, x, y);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (ctx->fractal->maxiter > ITER_MIN)
			ctx->fractal->maxiter -= ITER_DELTA;
		zoom(ctx->fractal, RATIO_LESS, x, y);
	}
	else
		return (0);
	draw_image(ctx);
	return (0);
}

void	on_keydown(int key, t_context *ctx)
{
	t_action				action;
	static const t_action	actions[MAX_KEYS] = {
		[BRACKET_LEFT] = change_fractal,
		[BRACKET_RIGHT] = change_fractal,
		[KEY_0] = change_maxiter,
		[MINUS] = change_maxiter,
		[PLUS] = change_maxiter,
		[ARROW_UP] = change_pan,
		[ARROW_DOWN] = change_pan,
		[ARROW_LEFT] = change_pan,
		[ARROW_RIGHT] = change_pan,
		[KEY_C] = change_cmap,
		[ESC] = unload
	};

	if (key <= MAX_KEYS && (action = actions[key]))
	{
		(*action)(key, ctx);
		draw_image(ctx);
	}
}

void	unload(int key, t_context *ctx)
{
	(void)key;
	(void)ctx;
	exit(EXIT_SUCCESS);
}
