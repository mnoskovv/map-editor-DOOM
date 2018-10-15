/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <aziabkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:47:45 by aziabkin          #+#    #+#             */
/*   Updated: 2018/10/04 20:02:08 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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

// while (all->rects)
// 	{
// 		if (y_mouse > all->rects->sdl_rect.y  && y_mouse <= all->rects->sdl_rect.y + (half_step * 2) 
// 			&& x_mouse > all->rects->sdl_rect.x  && x_mouse <= all->rects->sdl_rect.x + (half_step * 2))
// 		{
// 				if (all->rects->on_screen == 0)
// 				{
// 					printf("switched on 1\n");
// 					all->rects->on_screen = 1;
// 					all->rects->r = all->r;
// 					all->rects->g = all->g;
// 					all->rects->b = all->b;
// 					all->dogs[all->rects->y][all->rects->x] = all->bukva;
// 				}
// 				else
// 				{
// 					printf("switched on 0\n");
// 					all->rects->on_screen = 0;
// 					all->dogs[all->rects->y][all->rects->x] = ' ';
// 				}
// 				all->rects = start;
// 				return (1);
// 		}
// 		all->rects = all->rects->next;
// 	}


void	color_rects(int x_mouse, int y_mouse, t_all *all)
{
		if (y_mouse >= 33 && y_mouse <= 111 && x_mouse >= 965  && x_mouse <= 1004)
		{
			all->r = 0;
			all->g = 0;
			all->b = 0;
			all->bukva = 'Q';
		}
		if (y_mouse >= 33 && y_mouse <= 112 && x_mouse >= 1008  && x_mouse <= 1045)
		{
			all->r = 59;
			all->g = 101;
			all->b = 97;
			all->bukva = 'W';
		}
		if (y_mouse >= 33 && y_mouse <= 112 && x_mouse >= 1051  && x_mouse <= 1093)
		{
			all->r = 131;
			all->g = 54;
			all->b = 102;
			all->bukva = 'E';
		}
		if (y_mouse >= 33 && y_mouse <= 112 && x_mouse >= 1096  && x_mouse <= 1139)
		{
			all->r = 32;
			all->g = 164;
			all->b = 164;
			all->bukva = 'R';
		}
		if (y_mouse >= 33 && y_mouse <= 112 && x_mouse >= 1143  && x_mouse <= 1184)
		{
			all->r = 63;
			all->g = 45;
			all->b = 33;
			all->bukva = 'T';
		}

		if (y_mouse >= 114 && y_mouse <= 187 && x_mouse >= 965  && x_mouse <= 1004)
		{
			all->r = 122;
			all->g = 86;
			all->b = 51;
			all->bukva = 'Y';
		}
		if (y_mouse >= 114 && y_mouse <= 187 && x_mouse >= 1008  && x_mouse <= 1045)
		{
			all->r = 188;
			all->g = 31;
			all->b = 31;
			all->bukva = 'U';
		}
		if (y_mouse >= 114 && y_mouse <= 187 && x_mouse >= 1051  && x_mouse <= 1093)
		{
			all->r = 30;
			all->g = 19;
			all->b = 104;
			all->bukva = 'I';
		}
		if (y_mouse >= 114 && y_mouse <= 187 && x_mouse >= 1096  && x_mouse <= 1139)
		{
			all->r = 93;
			all->g = 93;
			all->b = 95;
			all->bukva = 'O';
		}
		if (y_mouse >= 114 && y_mouse <= 187 && x_mouse >= 1143  && x_mouse <= 1184)
		{
			all->r = 253;
			all->g = 127;
			all->b = 0;
			all->bukva = 'A';
		}
}

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
	rectangle->r = 255;
	rectangle->g = 0;
	rectangle->b = 255;
	rectangle->x = 0;
	rectangle->y = 0;
	rectangle->sdl_rect = sdl_rect;
	rectangle->index = 0;
	rectangle->is_player = 0;
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
	
	index = 0;
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
			printf("x = %d y = %d ix = %d iy = %d\n", all->rects->sdl_rect.x, all->rects->sdl_rect.y, all->rects->x, all->rects->y);
			all->rects = all->rects->next;
	}
}

void	valid_file(char *argv)
{
	if (ft_strstr(argv, "/dev/"))
		exit_error(1);
	if (!ft_strstr(argv, "maps/"))
		exit_error(1);
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
	char		*str;
	int			tmp_len;
	int			max_len;

	tmp_len = 0;
	max_len = 0;
	str = NULL;
	quit = false;
	x_mouse = 0;
	y_mouse = 0;
	if (argc != 2)
		exit_error(1);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	if ((all->fd = open(argv[1], O_RDWR)) == -1)
		exit_error(3);
	valid_file(argv[1]);
	if (get_next_line(all->fd, &str) == 0)
	{
		printf("Empty str\n"); //
		all->w = 51;
		all->h = 51;
	}
	else
	{
		printf("File doent empty\n"); //
		while (get_next_line(all->fd, &str) > 0)
		{
			tmp_len = ft_strlen(str);
			ft_strdel(&str);
			if (tmp_len > max_len)
				max_len = tmp_len;
		}
		all->max_strlen = max_len;
		printf("%i\n", all->max_strlen);
	}
	all->points = new_elem();
	all->rects = new_rect();
	start_r = all->rects;
	init_sdl(all);
	IMG_Init(IMG_INIT_PNG);
	SDL_Texture* texture = NULL;
	SDL_Surface* temp = IMG_Load("../map-editor-DOOM/walls.png");	//
    texture = SDL_CreateTextureFromSurface(all->rend, temp);//
    SDL_FreeSurface(temp);//
    SDL_Rect menu;
    menu.x = SCR_W - 250; //Extreme left of the window
    menu.y = 0; //Very bottom of the window
    menu.w = 250; //100 pixels width
    menu.h = 1000; //100 pixels height

	// all->w = ft_atoi(argv[1]) + 1;
	// all->h = ft_atoi(argv[2]) + 1;
	// if (!all->w || !all->h || all->h > 101 || all->w > 101
	// 						|| all->h < 5 || all->w < 5)
	// 	exit_error(2);
	if (!(dogs = load_dogs(all->w - 1, all->h - 1)))
		return (0);
	all->dogs = dogs;
	all->scale = (all->w > all->h) ? (SCR_W - 300) / all->w : (SCR_H - 50) / all->h;
	all->half_step = (all->scale ) / 2;
	all->r = 0;
	all->g = 0;
	all->b = 0;
	all->bukva = 'Q';
	create_list_points(all);
	start = all->points;
	neighbors(all);
	all->points = start;
	create_list_rects(all);
	all->points = start;
	all->sdl_player = NULL;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&x_mouse, &y_mouse);
				color_rects(x_mouse, y_mouse, all);
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_KP_ENTER)
				{	
					close(all->fd);
					all->fd = open(argv[1], O_RDWR);
					write_map(all);
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&x_mouse, &y_mouse);
					check_r(x_mouse, y_mouse, all, all->half_step);
				}
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					SDL_GetMouseState(&x_mouse, &y_mouse);
					pos_player(x_mouse, y_mouse, all, all->half_step);
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
 	   			SDL_SetRenderDrawColor(all->rend, all->rects->r, all->rects->g, all->rects->b, 0);
 	   			SDL_RenderFillRect(all->rend, &r);
			}
			all->rects = all->rects->next;
		}
		all->rects = start_r;
		if (all->sdl_player != NULL)
		{
			SDL_Rect r;

			SDL_SetRenderDrawColor(all->rend, 255, 232, 80, 0);
			r.x = all->sdl_player->x;
 	   		r.y = all->sdl_player->y;
 	   		r.w =  (all->half_step * 2) * 0.8 ;
 	   		r.h = (all->half_step * 2) * 0.8;
			SDL_RenderFillRect(all->rend, &r);
		}
		SDL_RenderCopy(all->rend, texture, NULL, &menu);
		SDL_RenderPresent(all->rend);
	}
	SDL_DestroyTexture(texture);
	IMG_Quit();
	f_close(all);
	return (1);
}
