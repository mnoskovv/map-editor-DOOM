/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <aziabkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:39:36 by aziabkin          #+#    #+#             */
/*   Updated: 2018/10/04 18:36:06 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int pos_player(int x_mouse,int y_mouse, t_all *all, int half_step)
{
	printf("click\n");
	printf("x click = %d y click = %d\n", x_mouse, y_mouse );
	t_rect *start;
	
	start = all->rects;
	while (all->rects)
	{
		if (y_mouse > all->rects->sdl_rect.y  && y_mouse <= all->rects->sdl_rect.y + (half_step * 2) 
			&& x_mouse > all->rects->sdl_rect.x  && x_mouse <= all->rects->sdl_rect.x + (half_step * 2))
		{
				if (all->sdl_player == NULL && all->rects->on_screen == 0)
				{
					printf("player switched on 1\n");
					all->rects->is_player = 1;
					all->sdl_player = new_rect();
					all->sdl_player->x = all->rects->sdl_rect.x + 5;
					all->sdl_player->y = all->rects->sdl_rect.y + 5;
					all->dogs[all->rects->y][all->rects->x] = 'P';
				}
				else if (all->rects->is_player == 1)
				{
					all->rects->is_player = 0;
					printf("player switched on 0\n");
					free(all->sdl_player);
					all->sdl_player = NULL;
					all->dogs[all->rects->y][all->rects->x] = ' ';
				}
				all->rects = start;
				return (1);
		}
		all->rects = all->rects->next;
	}
	all->rects = start;
	return (0);
}



int check_r(int x_mouse,int y_mouse, t_all *all, int half_step)
{
	printf("click\n");
	printf("x click = %d y click = %d\n", x_mouse, y_mouse );
	t_rect *start;
	
	start = all->rects;
	while (all->rects)
	{
		if (y_mouse > all->rects->sdl_rect.y  && y_mouse <= all->rects->sdl_rect.y + (half_step * 2) 
			&& x_mouse > all->rects->sdl_rect.x  && x_mouse <= all->rects->sdl_rect.x + (half_step * 2))
		{
				if (all->rects->on_screen == 0 && all->rects->is_player == 0)
				{
					printf("switched on 1\n");
					all->rects->on_screen = 1;
					all->rects->r = all->r;
					all->rects->g = all->g;
					all->rects->b = all->b;
					all->dogs[all->rects->y][all->rects->x] = all->bukva;
				}
				else 
				{
					printf("switched on 0\n");
					all->rects->on_screen = 0;
					all->dogs[all->rects->y][all->rects->x] = ' ';
				}
				all->rects = start;
				return (1);
		}
		all->rects = all->rects->next;
	}
	all->rects = start;
	return  (0);
}
