/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:47:45 by aziabkin          #+#    #+#             */
/*   Updated: 2018/09/20 17:47:46 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	main(int argc, char **argv)
{
	t_all		*all;
	t_points	*start;
	SDL_Event	e;
	bool		quit;
	int			x_mouse;
	int			y_mouse;

	quit = false;
	x_mouse = 0;
	y_mouse = 0;
	if (argc != 3)
		exit_error(1);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	all->points = new_elem();
	init_sdl(all);
	all->w = ft_atoi(argv[1]);
	all->h = ft_atoi(argv[2]);
	if (!all->w || !all->h || all->h > 100 || all->w > 100
							|| all->h < 4 || all->w < 4)
		exit_error(2);
	all->scale = (all->w > all->h) ? SCR_H / all->w : SCR_H / all->h;
	all->half_step = (all->scale + 20) / 2;
	all->zoom = 1;
	all->move = 0;
	create_list_points(all);
	start = all->points;
	neighbors(all);
	all->points = start;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;
			if (e.key.keysym.scancode == SDL_SCANCODE_D) // return in default position
				all->zoom = 1;
			if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y > 0)
					all->zoom *= 1.1;
				else if (e.wheel.y < 0 && all->zoom > 0.2)
				{
					all->zoom /= 1.1;
				}
				if (e.wheel.x > 0)
				{
					all->zoom *= 1.1;
				}
				else if (e.wheel.x < 0)
				{
					all->zoom /= 1.1;
			
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&x_mouse, &y_mouse);
					check(x_mouse, y_mouse, all, all->half_step);
				}
			}
		}
		SDL_SetRenderDrawColor(all->rend, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(all->rend);
		SDL_SetRenderDrawColor(all->rend, 0x00, 0x00, 0x00, 0x00);
		while (all->points)
		{
			draw(all, all->points->x, all->points->y);
			if (all->points->end_right)
				SDL_RenderDrawLine(all->rend, all->points->x * all->zoom, all->points->y * all->zoom,
					all->points->end_right->x * all->zoom, all->points->end_right->y * all->zoom);
			if (all->points->end_down)
				SDL_RenderDrawLine(all->rend, all->points->x * all->zoom, all->points->y * all->zoom,
					all->points->end_down->x * all->zoom, all->points->end_down->y * all->zoom);
			if (all->points->end_diag1)
				SDL_RenderDrawLine(all->rend, all->points->x * all->zoom, all->points->y * all->zoom,
					all->points->end_diag1->x * all->zoom, all->points->end_diag1->y * all->zoom);
			all->points = all->points->next;
		}
		all->points = start;
		SDL_RenderPresent(all->rend);
	}
	f_close(all);
	return (1);
}
