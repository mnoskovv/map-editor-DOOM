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
	app->player = NULL;
	all->zoom = 1;
	all->move = 0;
	create_list_points(all);
	start = all->points;
	neighbors(all);
	all->points = start;
	general_draw(all, start);
	f_close(all);
	return (1);
}