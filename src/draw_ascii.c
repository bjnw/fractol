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

#include <sys/ioctl.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "fractol.h"

#define RATIO_ASCII	3.8

static int	get_termwidth(void)
{
	struct winsize win;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	return (win.ws_col);
}

static void	iter_ascii(t_fractal *fractal, char *img,
				int width, int height)
{
	const char	*sym = " .:-8*o+)|&IH%*#";
	t_complex	c;
	t_tuple		t;
	int			x;
	int			y;

	c.im = fractal->ymax;
	y = 0;
	while (y < height)
	{
		c.re = fractal->xmin;
		x = 0;
		while (x < width)
		{
			t = fractal->iter(fractal, c);
			img[y * width + x] = sym[(int)t.iter % sizeof(sym)];
			c.re += fractal->dx;
			x++;
		}
		c.im -= fractal->dy;
		y++;
	}
}

void		draw_ascii(t_fractal *fractal)
{
	const int		width = get_termwidth();
	const int		height = width / RATIO_ASCII;
	const size_t	size = width * height;
	char			*img;

	img = xmalloc(size);
	fractal->dx = (fractal->xmax - fractal->xmin) / width;
	fractal->dy = (fractal->ymax - fractal->ymin) / height;
	iter_ascii(fractal, img, width, height);
	write(STDOUT_FILENO, img, size);
	free(img);
}
