/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <aziabkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:38:40 by aziabkin          #+#    #+#             */
/*   Updated: 2018/10/04 19:30:02 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

// # include <SDL2/SDL.h>
// # include <SDL2/SDL_image.h>
// # include "libft.h"
// # include "stdbool.h"
// # include <stdlib.h>
// # include <math.h>
// # include <fcntl.h>

# include <SDL.h>
# include <SDL_image.h>
# include "libft.h"
# include "stdbool.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define SCR_W 1200
# define SCR_H 1000
# define CHECK_RIGHT 0
# define CHECK_LEFT 1
# define CHECK_DIAG1 2
# define CHECK_DIAG2 3

typedef struct		s_rect
{
	SDL_Rect 		sdl_rect;
	int				x;
	int				y;
	int				r;
	int				g;
	int				b;
	int 			index;
	int				on_screen;
	int				is_player;
	struct s_rect	*next;
}					t_rect;

typedef struct		s_points
{
	int				x;
	int				y;
	struct s_points	*right;
	struct s_points	*down;
	struct s_points	*diag1;
	struct s_points	*end_right;
	struct s_points	*end_down;
	struct s_points	*end_diag1;
	struct s_points	*next;
}					t_points;

typedef struct		s_all
{
	SDL_Window		*wind;
	SDL_Renderer	*rend;
	t_points		*points;
	t_rect			*rects;
	t_rect			*r_start;
	t_rect			*sdl_player;
	char			**dogs;
	int				w;
	int				h;
	int				scale;
	int				half_step;
	int				fd;
	int				r;
	int				g;
	int				b;
	char			bukva;
	int				max_strlen;
}					t_all;

void				f_close(t_all *all);
void				create_list_points(t_all *all);
void				neighbors(t_all *all);
void				diag_l_r(t_all *all);
void				draw(t_all *all, int x, int y);
int 				check(int x_mouse,int y_mouse, t_all *all, int half_step);
int 				check_r(int x_mouse,int y_mouse, t_all *all, int half_step);
t_points			*new_elem(void);
void				exit_error(int n);
void				init_sdl(t_all *all);
void				general_draw(t_all *all, t_points *start);
void				set_render(t_all *all, t_points *start);
void				work(t_all *all, t_points *start);
void				color_rects(int x_mouse, int y_mouse, t_all *all);
void				write_map(t_all *all);
int					pos_player(int x_mouse, int y_mouse, t_all *all, int half_step);
t_rect				*new_rect();

#endif
