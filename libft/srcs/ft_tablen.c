/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:48:35 by amanuel           #+#    #+#             */
/*   Updated: 2018/12/27 15:25:17 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_tablen(void **tab)
{
	int			i;

	if (!(i = 0) && tab)
		while (tab[i])
			i++;
	return (i);
}
