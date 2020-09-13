/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sine_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:39:20 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:39:20 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fractol.h"

t_tuple	sine_mandelbrot(const t_fractal *fractal, t_complex c)
{
	t_complex	z;
	double		zrsq;
	double		zisq;
	int			n;

	z = NULL_COMPLEX;
	n = 0;
	while (n < fractal->maxiter)
	{
		zrsq = z.re * z.re;
		zisq = z.im * z.im;
		z = (t_complex){
			zrsq - zisq,
			2.0 * z.re * z.im
		};
		z = (t_complex){
			sin(z.re) * cosh(z.im) + c.re,
			cos(z.re) * sinh(z.im) + c.im
		};
		if (fabs(z.re) >= BAILOUT)
			return ((t_tuple){n, z.re});
		n++;
	}
	return (NULL_TUPLE);
}
