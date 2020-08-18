/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:48 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:51:48 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "fractol.h"
#include "mlx.h"

static void	plot(t_context *ctx, int x, int y, int color)
{
	const size_t offset = y * ctx->linesize + x * sizeof(int);

	*(int *)(ctx->addr + offset) = color;
}

void		draw_fractal(t_context *ctx, const t_fractal *fractal)
{
	t_complex	c;
	int			x;
	int			y;
	t_tuple		t;

	c.im = fractal->ymax;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		c.re = fractal->xmin;
		x = 0;
		while (x < WIN_WIDTH)
		{
			t = fractal->iter(fractal, c);
			plot(ctx, x, y, fractal->cmap(fractal, t));
			c.re += fractal->dx;
			x++;
		}
		c.im -= fractal->dy;
		y++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->data, 0, 0);
}
