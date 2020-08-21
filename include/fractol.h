/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 02:14:32 by ourgot            #+#    #+#             */
/*   Updated: 2020/07/28 02:14:32 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_WIDTH	1024
# define WIN_HEIGHT	857
# define WIN_TITLE	"fractol"

# define NUM_THREADS	8
# define SLICE_HEIGHT	WIN_HEIGHT / NUM_THREADS

# define MENU_WIDTH		600
# define MENU_HEIGHT	400
# define MENU_BGCOLOR	0xaa000000
# define MENU_TEXTCOLOR	0x00a0a0a0

# define BAILOUT		32
# define ITER_MIN		13
# define ITER_MAX		2048
# define ITER_DEFAULT	128

# define JULIA_RE	-0.702693
# define JULIA_IM	-0.384201

# define RATIO_MORE	1.077777
# define RATIO_LESS	0.927835

enum {
	MANDELBROT = 0,
	JULIA,
	BUFFALO,
	COSINE_MANDELBROT,
	PERPENDICULAR_MANDELBROT,
	PERPENDICULAR_CELTIC,
	BURNING_SHIP,
	ASCII_MANDELBROT
};

typedef struct	s_complex {
	double		re;
	double		im;
}				t_complex;

typedef struct	s_tuple {
	double		iter;
	double		sqmod;
}				t_tuple;

typedef struct s_fractal	t_fractal;
struct			s_fractal {
	int			maxiter;
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	double		dx;
	double		dy;
	t_complex	k;
	int			(*cmap)(const t_fractal *, t_tuple);
	t_tuple		(*iter)(const t_fractal *, t_complex);
};

typedef struct	s_context {
	void		*mlx;
	void		*win;
	void		*addr;
	void		*data;
	int			bpp;
	int			linesize;
	int			endian;
	t_fractal	*fractal;
}				t_context;

typedef struct	s_args {
	t_context	*ctx;
	int			from;
	int			until;
}				t_args;

typedef void	(*t_handler)(int, t_context *);
typedef int		(*t_cmap)(const t_fractal *, t_tuple);
typedef void	*(*t_routine)(void *);

void			init_fractal(t_fractal *fractal, int id);
void			draw_fractal(t_context *ctx);
void			draw_ascii(t_fractal *fractal);

void			draw_menu(t_context *ctx);

void			pan(t_fractal *fractal, double cx, double cy);
void			zoom(t_fractal *fractal, double zoom, double cx, double cy);

int				cmap_bernstein(const t_fractal *fractal, t_tuple t);
int				cmap_sine(const t_fractal *fractal, t_tuple t);
int				cmap_sepia(const t_fractal *fractal, t_tuple t);

t_tuple			mandelbrot(const t_fractal *fractal, t_complex c);
t_tuple			julia(const t_fractal *fractal, t_complex c);
t_tuple			buffalo(const t_fractal *fractal, t_complex c);
t_tuple			cosine_mandelbrot(const t_fractal *fractal, t_complex c);
t_tuple			perpendicular_mandelbrot(const t_fractal *fractal, t_complex c);
t_tuple			perpendicular_celtic(const t_fractal *fractal, t_complex c);
t_tuple			burning_ship(const t_fractal *fractal, t_complex c);

void			set_fractal(int key, t_context *ctx);
void			set_iter(int key, t_context *ctx);
void			set_pan(int key, t_context *ctx);
void			set_cmap(int key, t_context *ctx);

int				on_mousedown(int button, int x, int y, t_context *ctx);
int				on_mousemove(int x, int y, t_context *ctx);
void			on_keydown(int key, t_context *ctx);
void			unload(int key, t_context *ctx);

#endif
