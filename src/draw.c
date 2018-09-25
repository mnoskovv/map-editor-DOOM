/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:42:41 by aziabkin          #+#    #+#             */
/*   Updated: 2018/09/20 17:42:43 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw(t_all *all, int x, int y)
{
	// SDL_RenderDrawPoint(all->rend, (x * all->zoom) , (y * all->zoom));
	SDL_RenderDrawPoint(all->rend, (x * all->zoom) + 1, (y * all->zoom) + 1);
	SDL_RenderDrawPoint(all->rend, (x * all->zoom) + 1, (y * all->zoom));
	SDL_RenderDrawPoint(all->rend, (x * all->zoom) + 1, (y * all->zoom) - 1);
	SDL_RenderDrawPoint(all->rend, (x * all->zoom), (y * all->zoom) + 1);
	SDL_RenderDrawPoint(all->rend, (x * all->zoom), (y * all->zoom) - 1);
	SDL_RenderDrawPoint(all->rend, (x * all->zoom), (y * all->zoom));
	SDL_RenderDrawPoint(all->rend, (x * all->zoom) - 1, (y * all->zoom) + 1);
	SDL_RenderDrawPoint(all->rend, (x * all->zoom) - 1, (y * all->zoom));
	SDL_RenderDrawPoint(all->rend, (x * all->zoom) - 1, (y * all->zoom) - 1);
}

void	work(t_all *all, t_points *start)
{
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
		if (all->points->right && all->points->right->end_diag2)
			SDL_RenderDrawLine(all->rend, all->points->right->x * all->zoom, \
				all->points->right->y * all->zoom, all->points->right->end_diag2->x * all->zoom, \
				all->points->right->end_diag2->y * all->zoom);
		all->points = all->points->next;
	}
	all->points = start;
}

void	set_render(t_all *all, t_points *start)
{
	SDL_SetRenderDrawColor(all->rend, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(all->rend);
	SDL_SetRenderDrawColor(all->rend, 0x00, 0x00, 0x00, 0x00);
	work(all, start);
	SDL_RenderPresent(all->rend);
}

// bool on_wall(int x_mouse,int y_mouse,t_all *all)
// {


//     return (true);
// }

// void    put_player(int x_mouse,int y_mouse,t_all *all, t_points *start)
// {
//     if (on_wall(x_mouse, y_mouse, all, start) == false)
        
// }
void	general_draw(t_all *all, t_points *start)
{
	SDL_Event	e;
	bool		quit;
	int			x_mouse;
	int			y_mouse;

	quit = false;
	x_mouse = 0;
	y_mouse = 0;
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
				{
					all->zoom *= 1.3;
					printf("tut111\n");
					printf("%d\n", e.wheel.y);
				}
				else if (e.wheel.y < 0)
				{
					all->zoom /= 1.3;
					printf("tut222\n");
				}
				if (e.wheel.x > 0)
				{
					all->zoom *= 1.3;
					printf("tut333\n");
				}
				else if (e.wheel.x < 0)
				{
					all->zoom /= 1.3;
					printf("tut444\n");
				}
			}
   			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&x_mouse, &y_mouse);
					check(x_mouse, y_mouse, all);
				}
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					SDL_GetMouseState(&x_mouse, &y_mouse);
					// put_player(x_mouse, y_mouse, all, start);
					printf("поставить игрока\n");
				}
			}
		}
		set_render(all, start);
	}
}
