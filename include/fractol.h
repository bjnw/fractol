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
# define WIN_HEIGHT	856
# define WIN_TITLE	"fractol"

enum {
	MANDELBROT = 0,
	JULIA,
	BUFFALO,
	COSINE_MANDELBROT,
	PERPENDICULAR_MANDELBROT,
	PERPENDICULAR_CELTIC,
	BURNING_SHIP
};

# define ITER_DEFAULT	128
# define ITER_MIN		13
# define ITER_MAX		2048
# define BAILOUT		32

# define JULIA_RE	-0.702693
# define JULIA_IM	-0.384201

# define RATIO_MORE	1.077777
# define RATIO_LESS	0.927835

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
	t_tuple		(*iter)(const t_fractal *, t_complex);
};

typedef struct s_context	t_context;
struct			s_context {
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bpp;
	int			linesize;
	int			endian;
	int			width;
	int			height;
	t_fractal	*fractal;
	void		(*plot)(t_context *, int, int, int);
	int			(*cmap)(const t_fractal *, t_tuple);
};

typedef struct	s_arg {
	t_context	*ctx;
	int			ymin;
	int			ymax;
}				t_arg;

typedef void	*(*t_worker)(void *);
typedef void	(*t_action)(int, t_context *);
typedef int		(*t_cmap)(const t_fractal *, t_tuple);

void			init_fractal(t_fractal *fractal, int id);
void			init_mlx_ctx(t_context *ctx, t_fractal *fractal);
void			init_ascii_ctx(t_context *ctx, t_fractal *fractal);

void			draw_image(t_context *ctx);
void			draw_ascii(t_context *ctx);

void			show_menu(t_context *ctx);

t_tuple			mandelbrot(const t_fractal *fractal, t_complex c);
t_tuple			julia(const t_fractal *fractal, t_complex c);
t_tuple			buffalo(const t_fractal *fractal, t_complex c);
t_tuple			cosine_mandelbrot(const t_fractal *fractal, t_complex c);
t_tuple			perpendicular_mandelbrot(const t_fractal *fractal, t_complex c);
t_tuple			perpendicular_celtic(const t_fractal *fractal, t_complex c);
t_tuple			burning_ship(const t_fractal *fractal, t_complex c);

void			pan(t_fractal *fractal, double cx, double cy);
void			zoom(t_fractal *fractal, double zoom, double cx, double cy);

void			plot_image(t_context *ctx, int x, int y, int color);
void			plot_ascii(t_context *ctx, int x, int y, int color);

int				cmap_bernstein(const t_fractal *fractal, t_tuple t);
int				cmap_sine(const t_fractal *fractal, t_tuple t);
int				cmap_sepia(const t_fractal *fractal, t_tuple t);
int				cmap_ascii(const t_fractal *fractal, t_tuple t);

void			change_fractal(int key, t_context *ctx);
void			change_maxiter(int key, t_context *ctx);
void			change_pan(int key, t_context *ctx);
void			change_cmap(int key, t_context *ctx);

int				on_mousedown(int button, int x, int y, t_context *ctx);
int				on_mousemove(int x, int y, t_context *ctx);
void			on_keydown(int key, t_context *ctx);
void			unload(int key, t_context *ctx);

#endif
