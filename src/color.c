/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 19:17:48 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/07 19:17:48 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fractol.h"
#include "libft.h"

static int	hsv_to_rgb(double h, double s, double v)
{
	const int		i = (int)(h / 60);
	const double	f = h / 60 - i;
	const double	p = v * (1.0 - s);
	const double	q = v * (1.0 - s * f);
	const double	t = v * (1.0 - s * (1.0 - f));

	if (i < 1)
		return ((int)(255 * v) << 16 | (int)(255 * t) << 8 | (int)(255 * p));
	if (i < 2)
		return ((int)(255 * q) << 16 | (int)(255 * v) << 8 | (int)(255 * p));
	if (i < 3)
		return ((int)(255 * p) << 16 | (int)(255 * v) << 8 | (int)(255 * t));
	if (i < 4)
		return ((int)(255 * p) << 16 | (int)(255 * q) << 8 | (int)(255 * v));
	if (i < 5)
		return ((int)(255 * t) << 16 | (int)(255 * p) << 8 | (int)(255 * v));
	return ((int)(255 * v) << 16 | (int)(255 * p) << 8 | (int)(255 * q));
}

int			color_bernstein(const t_fractal *fractal, t_tuple t)
{
	double	v;
	int		c;
	int		r;
	int		g;
	int		b;

	if (t.iter == 0)
		return (0);
	// v = (t.iter - log2(log2(t.sqmod))) / fractal->maxiter;
	v = tanh(2 * (t.iter + 1 - log2(log2(t.sqmod))) / fractal->maxiter);
	if (v < 0)
		return (0);
	c = ft_rand() & 3;
	r = 9 * (1 - v) * v * v * v * (255 - c) + c;
	g = 15 * (1 - v) * (1 - v) * v * v * (255 - c) + c;
	b = 8.5 * (1 - v) * (1 - v) * (1 - v) * v * (255 - c) + c;
	return (r << 16 | g << 8 | b);
}

int			color_sine(const t_fractal *fractal, t_tuple t)
{
	double	v;
	int		c;

	if (t.iter == 0)
		return (0);
	c = ft_rand() & 3;
	v = (t.iter - log2(log2(t.sqmod))) / fractal->maxiter;
	// v = tanh(2 * (t.iter - log2(log2(t.sqmod))) / fractal->maxiter);
	v = fabs(cos(2 * M_PI * v)) * (360 - c) + c;
	return (hsv_to_rgb(v, 0.71, 0.79));
}
