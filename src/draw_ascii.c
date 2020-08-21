/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:48 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:51:48 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"
#include "fractol.h"

// static void	iter_ascii(const t_args *args)
// {
// 	const t_fractal	*fractal = args->ctx->fractal;
// 	t_complex		c;
// 	int				x;
// 	int				y;
// 	t_tuple			t;

// 	c.im = fractal->ymax - fractal->dy * args->from;
// 	y = args->from;
// 	while (y < args->until)
// 	{
// 		c.re = fractal->xmin;
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			t = fractal->iter(fractal, c);
// 			plot(args->ctx, x, y, fractal->cmap(fractal, t));
// 			c.re += fractal->dx;
// 			x++;
// 		}
// 		c.im -= fractal->dy;
// 		y++;
// 	}
// }

// void		draw_ascii(t_fractal *fractal)
// {
// }
