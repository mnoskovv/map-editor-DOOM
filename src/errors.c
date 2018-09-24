/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:46:41 by aziabkin          #+#    #+#             */
/*   Updated: 2018/09/20 17:46:45 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	exit_error(int n)
{
	if (n == 1)
	{
		ft_putstr("Two arguments required!:");
		ft_putendl(" ./editor arg_1 > 4 && < 100 arg_2 > 4 && < 100");
	}
	else if (n == 2)
	{
		ft_putstr("Wrong size!:");
		ft_putendl(" ./editor arg_1 > 4 && < 100 arg_2 > 4 && < 100");
	}
	else if (n == 3)
	{
		ft_putstr("SDL couldn't initialize! SDL Error: ");
		ft_putendl(SDL_GetError());
	}
	exit(0);
}
