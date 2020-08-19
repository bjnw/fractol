/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_additional.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:39:20 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:39:20 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fractol.h"

/*
** z = c + pi * cos(z)
*/

t_tuple		mandelbrot_cos(const t_fractal *fractal, t_complex c)
{
	t_complex	z;
	int			n;

	z = (t_complex){0, 0};
	n = 0;
	while (n < fractal->maxiter)
	{
		z = (t_complex){
			M_PI * cos(z.re) * cosh(z.im) + c.re,
			M_PI * -sin(z.re) * sinh(z.im) + c.im
		};
		if (fabs(z.im) >= BAILOUT)
			return ((t_tuple){n, z.im});
		n++;
	}
	return ((t_tuple){0, 0});
}

t_tuple		perpendicular_celtic(const t_fractal *fractal, t_complex c)
{
	t_complex	z;
	double		zrsq;
	double		zisq;
	int			n;

	z = (t_complex){0, 0};
	n = 0;
	while (n < fractal->maxiter)
	{
		zrsq = z.re * z.re;
		zisq = z.im * z.im;
		z = (t_complex){
			fabs(zrsq - zisq) + c.re,
			-2.0 * fabs(z.re) * z.im + c.im
		};
		if (zrsq + zisq >= BAILOUT)
			return ((t_tuple){n, zrsq + zisq});
		n++;
	}
	return ((t_tuple){0, 0});
}

t_tuple		perpendicular_mandelbrot(const t_fractal *fractal, t_complex c)
{
	t_complex	z;
	double		zrsq;
	double		zisq;
	int			n;

	z = (t_complex){0, 0};
	n = 0;
	while (n < fractal->maxiter)
	{
		zrsq = z.re * z.re;
		zisq = z.im * z.im;
		z = (t_complex){
			zrsq - zisq + c.re,
			-2.0 * fabs(z.re) * z.im + c.im
		};
		if (zrsq + zisq >= BAILOUT)
			return ((t_tuple){n, zrsq + zisq});
		n++;
	}
	return ((t_tuple){0, 0});
}

t_tuple		burning_ship(const t_fractal *fractal, t_complex c)
{
	t_complex	z;
	double		zrsq;
	double		zisq;
	int			n;

	z = (t_complex){0, 0};
	n = 0;
	while (n < fractal->maxiter)
	{
		zrsq = z.re * z.re;
		zisq = z.im * z.im;
		z = (t_complex){
			zrsq - zisq + c.re,
			-2.0 * fabs(z.re * z.im) + c.im
		};
		if (zrsq + zisq >= BAILOUT)
			return ((t_tuple){n, zrsq + zisq});
		n++;
	}
	return ((t_tuple){0, 0});
}
