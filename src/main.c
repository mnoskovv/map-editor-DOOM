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

void	read_file(t_all *all, char *way)
{
	char	*str;
	int		max_l_h[2];

	all->tmp_len = 0;
	max_l_h[0] = 0;
	max_l_h[1] = 0;
	str = NULL;
	while (get_next_line(all->fd, &str) > 0)
	{
		all->emptyness_flag = 0;
		all->tmp_len = ft_strlen(str);
		if (all->tmp_len > max_l_h[0])
			max_l_h[0] = all->tmp_len;
		max_l_h[1]++;
		free(str);
	}
	if (all->emptyness_flag == -1)
		all->tmp_len = 30;
	else
	{
		all->tmp_len = (max_l_h[1] - 5 > max_l_h[0] - 4) ?\
							max_l_h[1] - 5 : max_l_h[0] - 4;
		close(all->fd);
		all->fd = open(way, O_RDWR);
	}
}

void	init_1(t_all *all, char *way)
{
	char	**dogs;

	if (!(dogs = load_dogs(all->w - 1, all->h - 1)))
		return ;
	all->dogs = dogs;
	all->scale = (all->w > all->h) ?\
			(SCR_W - 300) / all->w : (SCR_H - 80) / all->h;
	all->half_step = (all->scale) / 2;
	all->r = 0;
	all->g = 0;
	all->b = 0;
	all->bukva = 'D';
	read_map(way, all);
}

void	init(t_all *all, char *way)
{
<<<<<<< HEAD
	all->texture = NULL;
	if ((all->fd = open(way, O_RDWR)) == -1)
		exit_error(3);
	valid_file(way);
	all->emptyness_flag = -1;
	read_file(all, way);
	all->w = all->tmp_len + 1;
	all->h = all->tmp_len + 1;
	all->points = new_elem();
	all->rects = new_rect();
	all->r_start = all->rects;
	init_sdl(all);
	all->temp = IMG_Load("../map-editor-DOOM/walls.png");
	IMG_Init(IMG_INIT_PNG);
	all->texture = SDL_CreateTextureFromSurface(all->rend, all->temp);
	SDL_FreeSurface(all->temp);
	all->menu.x = SCR_W - 250;
	all->menu.y = 0;
	all->menu.w = 250;
	all->menu.h = 1000;
=======
	if (ft_strstr(argv, "/dev/"))
		exit_error(1);
	if (!ft_strstr(argv, "maps/"))
		exit_error(1);
>>>>>>> d899ab428c1d5715194fb996b51bb7256a2607f7
}

int		main(int argc, char **argv)
{
	t_all		*all;
	t_points	*start;
<<<<<<< HEAD

=======
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
>>>>>>> d899ab428c1d5715194fb996b51bb7256a2607f7
	if (argc != 2)
		exit_error(1);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
<<<<<<< HEAD
	init(all, argv[1]);
	init_1(all, argv[1]);
	create_list1(all);
=======
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
>>>>>>> d899ab428c1d5715194fb996b51bb7256a2607f7
	start = all->points;
	neighbors(all);
	all->points = start;
	create_list_rects(all);
	all->rects = all->r_start;
	all->points = start;
	all->sdl_player = NULL;
	if (all->emptyness_flag == 0)
	{
<<<<<<< HEAD
		load_rects(all);
		all->rects = all->r_start;
=======
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
>>>>>>> d899ab428c1d5715194fb996b51bb7256a2607f7
	}
	general_draw(all, start, argv[1]);
	return (1);
}
