/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:39:20 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:39:20 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fractol.h"

t_tuple	julia(const t_fractal *fractal, t_complex c)
{
	const t_complex	k = fractal->k;
	t_complex		z;
	double			zrsq;
	double			zisq;
	int				n;

	z = c;
	n = 0;
	while (n < fractal->maxiter)
	{
		zrsq = z.re * z.re;
		zisq = z.im * z.im;
		z = (t_complex){
			zrsq - zisq + k.re,
			2.0 * z.re * z.im + k.im
		};
		if (zrsq + zisq >= BAILOUT)
			return ((t_tuple){n, zrsq + zisq});
		n++;
	}
	return ((t_tuple){0, 0});
}
