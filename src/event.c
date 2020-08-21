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

#include <stdlib.h>

#include "fractol.h"
#include "keys.h"
#include "mlx.h"

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
		[KEY_7] = set_fractal,
		[KEY_8] = set_fractal,
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

void	unload(int key, t_context *ctx)
{
	(void)key;
	(void)ctx;
	exit(EXIT_SUCCESS);
}
