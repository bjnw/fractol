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
#include <pthread.h>

#include "libft.h"
#include "fractol.h"
#include "mlx.h"

static void	plot(t_context *ctx, int x, int y, int color)
{
	const size_t offset = y * ctx->linesize + x * sizeof(int);

	*(int *)(ctx->addr + offset) = color;
}

static void	draw_part(const t_args *args)
{
	const t_fractal	*fractal = args->ctx->fractal;
	t_complex		c;
	int				x;
	int				y;
	t_tuple			t;

	c.im = fractal->ymax - fractal->dy * args->from;
	y = args->from;
	while (y < args->until)
	{
		c.re = fractal->xmin;
		x = 0;
		while (x < WIN_WIDTH)
		{
			t = fractal->iter(fractal, c);
			plot(args->ctx, x, y, fractal->cmap(fractal, t));
			c.re += fractal->dx;
			x++;
		}
		c.im -= fractal->dy;
		y++;
	}
}

void		draw_fractal(t_context *ctx)
{
	static pthread_t	threads[NUM_THREADS];
	static t_args		args[NUM_THREADS];
	int					n;

	n = NUM_THREADS;
	while (n--)
	{
		args[n].ctx = ctx;
		args[n].from = SLICE_HEIGHT * n;
		args[n].until = SLICE_HEIGHT * (n + 1);
		if (pthread_create(&threads[n], NULL,
					(void *(*)(void *))draw_part, &args[n]))
			panic("error: threads");
	}
	n = NUM_THREADS;
	while (n--)
	{
		if (pthread_join(threads[n], NULL))
			panic("error: threads");
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->data, 0, 0);
}
