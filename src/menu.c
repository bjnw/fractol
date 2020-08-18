/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:48 by ourgot            #+#    #+#             */
/*   Updated: 2020/08/01 01:51:48 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"

static void	draw_menu_bg(t_context *menu)
{
	const int	*last_pixel = menu->addr + MENU_WIDTH * MENU_HEIGHT;
	int			*img_ptr;

	img_ptr = menu->addr;
	while (img_ptr <= last_pixel)
		*img_ptr++ = MENU_BGCOLOR;
}

static void	draw_menu_text(t_context *ctx)
{
	static int y;
	mlx_string_put(ctx->mlx, ctx->win, 10, y += 10, MENU_TEXTCOLOR, "test");
}

static void	init_menu(t_context *ctx, t_context *menu)
{
	menu->data = mlx_new_image(ctx->mlx, MENU_WIDTH, MENU_HEIGHT);
	menu->addr = mlx_get_data_addr(menu->data, &menu->bpp,
			&menu->linesize, &menu->endian);
	draw_menu_bg(ctx);
	draw_menu_text(ctx);
}

void		draw_menu(t_context *ctx)
{
	static t_context	menu;
	static const int	x = (WIN_WIDTH - MENU_WIDTH) / 2;
	static const int	y = (WIN_WIDTH - MENU_WIDTH) / 2;

	if (menu.data == NULL)
		init_menu(ctx, &menu);
	mlx_put_image_to_window(ctx->mlx, ctx->win, menu.data, x, y);
}
