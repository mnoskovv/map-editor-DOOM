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
char **load_dogs(int w, int h)
{
	char **dogs;
	int x;
	int y;

	y = 0;
	if (!(dogs = (char **)malloc(sizeof(dogs) * h + 1)))
		return (NULL);
	dogs[h] = 0;
	while (y < h)
	{
		if (!(dogs[y] = (char *)malloc(sizeof(dogs[y]) * w + 1)))
			return (NULL);
		y++;
	}
	y = 0;
	x = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			
			dogs[y][x] = '@';
			x++;
		}
		dogs[y][x] = '\0';
		y++;
	}
	return (dogs);
}

t_rect	*new_rect(t_all *all,int x, int y, int index)
{
	t_rect *rectangle;
	SDL_Rect sdl_rect;

	if (!(rectangle = (t_rect *)malloc(sizeof(t_rect))))
		return (NULL);
	sdl_rect.x = x;
	sdl_rect.y = y;
	sdl_rect.w = all->half_step * 2;
	sdl_rect.h = all->half_step * 2;
	rectangle->sdl_rect = sdl_rect;
	rectangle->index = index;

	rectangle->next = NULL;
	return (rectangle); 
}

void create_list_rects(t_all *all) // тут надо подумать о правильном создании листа квадратов
{
	// t_rect *rect;
	t_rect *rect_start;

	rect_start = all->rects;
	// int 	index = 0;
	while (all->points->next)
	{
		if (all->points->right && all->points->down && all->points->diag1)
		{
			all->rects = new_rect(all ,all->points->x, all->points->y, 0);
			all->rects = all->rects->next;
			// тут типа если все точки остальные есть, то можно сделать из нее квадрат
			// и обяззательно связать эту ноду, что создалать и будующую, если она будет, а если нет, то NULL

			//  а этом месте нужно считать индекс по идее. Чтобы его можно было потом передавать. Но я не знаю 
			// пока как его считать, надо придумать, или сделать 2 индекса, по Х и по У
		}
		all->points = all->points->next;
	}
	all->rects = rect_start;
}
int	main(int argc, char **argv)
{
	t_all		*all;
	t_points	*start;
	t_rect		*rect_start;
	SDL_Event	e;
	bool		quit;
	int			x_mouse;
	int			y_mouse;
	char 		**dogs;
 	t_rect		*rects = NULL; // создать под него структуру и закинуть эту структуру в all

	quit = false;
	x_mouse = 0;
	y_mouse = 0;
	if (argc != 3)
		exit_error(1);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	all->points = new_elem();
	init_sdl(all);
	all->w = ft_atoi(argv[1]) + 1;
	all->h = ft_atoi(argv[2]) + 1;
	if (!all->w || !all->h || all->h > 100 || all->w > 100  // обратить внимание на 3х3 +1 
							|| all->h < 4 || all->w < 4)	//
		exit_error(2);
	if (!(dogs = load_dogs(all->w - 1, all->h - 1)))
		return (0);
	for (int i = 0; i < all->h - 1; i++)
	{
		printf("%s\n", dogs[i]);
	}
	all->rects = rects;
	all->scale = (all->w > all->h) ? SCR_H / all->w : SCR_H / all->h;
	all->half_step = (all->scale ) / 2;
	all->zoom = 1;
	all->move = 0;
	create_list_points(all);
	start = all->points;
	neighbors(all);
	all->points = start;
	create_list_rects(all);
	rect_start = all->rects;
	all->points = start;

	while (all->rects)
	{
		printf("x = %d y = %d\n", all->rects->sdl_rect.x, all->rects->sdl_rect.y);
		all->rects = all->rects->next;
	}
	// SDL_Rect r;
 	//    r.x = all->points->x;
 	//    r.y = all->points->y;
 	//    r.w = all->half_step * 2;
 	//    r.h = all->half_step * 2;

	//    SDL_Rect r2;
	//    r2.x = all->points->next->x;
	//    r2.y = all->points->next->y;
	//    r2.w = all->half_step * 2;
	//    r2.h = all->half_step * 2;

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
		// SDL_SetRenderDrawColor(all->rend, 0, 0, 255, 255 );
  //  		SDL_RenderFillRect( all->rend, &r );
  //  		SDL_RenderFillRect( all->rend, &r2 );
		all->points = start;
		SDL_RenderPresent(all->rend);
	}
	f_close(all);
	return (1);
}
