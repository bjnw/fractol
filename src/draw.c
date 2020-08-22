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

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "fractol.h"
#include "mlx.h"

#define NUM_THREADS		8
#define SLICE_HEIGHT	WIN_HEIGHT / NUM_THREADS

void		plot_image(t_context *ctx, int x, int y, int color)
{
	const size_t offset = y * ctx->linesize + x * sizeof(int);

	*(int *)(ctx->addr + offset) = color;
}

void		plot_ascii(t_context *ctx, int x, int y, int color)
{
	const size_t offset = y * ctx->width + x;

	*((char *)ctx->img + offset) = color;
}

static void	yield(const t_arg *arg)
{
	const t_fractal	*fractal = arg->ctx->fractal;
	t_complex		c;
	t_tuple			t;
	int				x;
	int				y;

	c.im = fractal->ymax - fractal->dy * arg->ymin;
	y = arg->ymin;
	while (y < arg->ymax)
	{
		c.re = fractal->xmin;
		x = 0;
		while (x < arg->ctx->width)
		{
			t = fractal->iter(fractal, c);
			arg->ctx->plot(arg->ctx, x, y,
					arg->ctx->cmap(fractal, t));
			c.re += fractal->dx;
			x++;
		}
		c.im -= fractal->dy;
		y++;
	}
}

void		draw_image(t_context *ctx)
{
	static pthread_t	threads[NUM_THREADS];
	t_arg				args[NUM_THREADS];
	int					n;

	n = NUM_THREADS;
	while (n--)
	{
		args[n].ctx = ctx;
		args[n].ymin = SLICE_HEIGHT * n;
		args[n].ymax = SLICE_HEIGHT * (n + 1);
		if (pthread_create(&threads[n], NULL,
				(t_worker)yield, &args[n]))
			panic("error: pthread_create");
	}
	n = NUM_THREADS;
	while (n--)
	{
		if (pthread_join(threads[n], NULL))
			panic("error: pthread_join");
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img, 0, 0);
}

void		draw_ascii(t_context *ctx)
{
	yield(&(t_arg){ctx, 0, ctx->height});
	write(STDOUT_FILENO, ctx->img, ctx->width * ctx->height);
	free(ctx->img);
}
