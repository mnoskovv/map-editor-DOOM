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
			
			dogs[y][x] = ' ';
			x++;
		}
		dogs[y][x] = '\0';
		y++;
	}
	return (dogs);
}

t_rect	*new_rect()
{
	t_rect		*rectangle;
	SDL_Rect	sdl_rect;

	if (!(rectangle = (t_rect *)malloc(sizeof(t_rect))))
		return (NULL);
	sdl_rect.x = 0;
	sdl_rect.y = 0;
	sdl_rect.w = 0;
	sdl_rect.h = 0;
	rectangle->sdl_rect = sdl_rect;
	rectangle->index = 0;
	rectangle->on_screen = 0;
	rectangle->next = NULL;
	return (rectangle); 
}


void	put_rect(t_all *all,int x, int y, int ix, int iy)
{
	all->rects->sdl_rect.x = x;
	all->rects->sdl_rect.y = y;
	all->rects->sdl_rect.w = all->half_step * 2;
	all->rects->sdl_rect.h = all->half_step * 2;
	all->rects->x = ix;
	all->rects->y = iy;
}

void create_list_rects(t_all *all) // тут надо подумать о правильном создании листа квадратов
{
	t_rect	*start;
	int 	index;
	int		iy;
	int		ix;
	
	i = 0;
	iy = -1;
	ix = -1;
	start = all->rects;
	while (all->points)
	{
		if (all->points->right && all->points->down && all->points->diag1 && index++ < (all->w - 1) * (all->h - 1))
		{
			if (++iy == all->h - 1)
			{
				if (iy == all->h - 1)
					ix++;
				iy = 0;
			}
			put_rect(all ,all->points->x, all->points->y, ix, iy);
			if (index < (all->w - 1) * (all->h - 1))
			{
				all->rects->next = new_rect();
				all->rects = all->rects->next;
			}
		}
		all->points = all->points->next;
	}
	all->rects->next = NULL;
	all->rects = start;

	while (all->rects)
	{
			// index++;
			printf("x = %d y = %d ix = %d iy = %d\n", all->rects->sdl_rect.x, all->rects->sdl_rect.y, all->rects->x, all->rects->y);
			all->rects = all->rects->next;
	}

	// printf("k = %d\n", index);
	
}

void write_map(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->h - 1)
	{
		ft_putendl_fd(all->dogs[i], all->fd);
		printf("%s\n", all->dogs[i]); // DELETEEEE	
	}
}

int	main(int argc, char **argv)
{
	t_all		*all;
	t_points	*start;
	t_rect		*start_r;
	SDL_Event	e;
	bool		quit;
	int			x_mouse;
	int			y_mouse;
	char 		**dogs;

	quit = false;
	x_mouse = 0;
	y_mouse = 0;
	if (argc != 4)
		exit_error(1);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	if ((all->fd = open(argv[3], O_RDWR)) == -1)
		exit_error(4);
	all->points = new_elem();
	all->rects = new_rect();
	start_r = all->rects;
	init_sdl(all);
	all->w = ft_atoi(argv[1]) + 1;
	all->h = ft_atoi(argv[2]) + 1;
	if (!all->w || !all->h || all->h > 100 || all->w > 100  // обратить внимание на 3х3 +1 
							|| all->h < 4 || all->w < 4)	//
		exit_error(2);
	if (!(dogs = load_dogs(all->w - 1, all->h - 1)))
		return (0);
	all->dogs = dogs;
	all->scale = (all->w > all->h) ? SCR_H / all->w : SCR_H / all->h;
	all->half_step = (all->scale ) / 2;
	all->r = 0;
	all->g = 102;
	all->b = 0;
	create_list_points(all);
	start = all->points;
	neighbors(all);
	all->points = start;
	create_list_rects(all);
	all->points = start;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_p)
					write_map(all);
				if (e.key.keysym.sym == SDLK_q)
				{
					all->r = 179;
					all->g = 0;
					all->b = 0;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&x_mouse, &y_mouse);
					check_r(x_mouse, y_mouse, all, all->half_step);
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
				SDL_RenderDrawLine(all->rend, all->points->x, all->points->y,
					all->points->end_right->x, all->points->end_right->y);
			if (all->points->end_down)
				SDL_RenderDrawLine(all->rend, all->points->x, all->points->y,
					all->points->end_down->x, all->points->end_down->y);
			if (all->points->end_diag1)
				SDL_RenderDrawLine(all->rend, all->points->x, all->points->y,
					all->points->end_diag1->x, all->points->end_diag1->y);
			all->points = all->points->next;
		}
		all->points = start;
		while (all->rects)
		{
			if (all->rects->on_screen == 1)
			{
				SDL_Rect r;
 	   			r.x = all->rects->sdl_rect.x;
 	   			r.y = all->rects->sdl_rect.y;
 	   			r.w = all->half_step * 2;
 	   			r.h = all->half_step * 2;
 	   			SDL_SetRenderDrawColor(all->rend, all->r, all->g, all->b, 0);
 	   			SDL_RenderFillRect(all->rend, &r);
			}
			all->rects = all->rects->next;
		}
		all->rects = start_r;
		SDL_RenderPresent(all->rend);
	}
	f_close(all);
	return (1);
}
