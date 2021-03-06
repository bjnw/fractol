/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:39:20 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:39:20 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fractol.h"

t_tuple	burning_ship(const t_fractal *fractal, t_complex c)
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
			zrsq - zisq + c.re,
			-2.0 * fabs(z.re * z.im) + c.im
		};
		if (zrsq + zisq >= BAILOUT)
			return ((t_tuple){n, zrsq + zisq});
		n++;
	}
	return (NULL_TUPLE);
}
