/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 19:15:15 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/07 19:15:15 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pan(t_fractal *fractal, double cx, double cy)
{
	const double dr = fractal->dx * cx;
	const double di = fractal->dy * cy;

	fractal->xmin += dr;
	fractal->xmax += dr;
	fractal->ymin -= di;
	fractal->ymax -= di;
}

void	zoom(t_fractal *fractal, double zoom, double cx, double cy)
{
	const double dr = cx * fractal->dx * (1 - 1 / zoom);
	const double di = cy * fractal->dy * (1 - 1 / zoom);

	fractal->xmin += dr;
	fractal->xmax += dr;
	fractal->ymin -= di;
	fractal->ymax -= di;
	fractal->dx /= zoom;
	fractal->dy /= zoom;
}
