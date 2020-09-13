/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosine_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:39:20 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:39:20 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fractol.h"

t_tuple	cosine_mandelbrot(const t_fractal *fractal, t_complex c)
{
	t_complex	z;
	int			n;

	z = NULL_COMPLEX;
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
	return (NULL_TUPLE);
}
