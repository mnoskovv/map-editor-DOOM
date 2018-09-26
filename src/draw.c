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
