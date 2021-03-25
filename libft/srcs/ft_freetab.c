/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:00:23 by amanuel           #+#    #+#             */
/*   Updated: 2018/12/27 15:23:38 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_freetab(void ***tab)
{
	int		i;

	if (tab)
	{
		i = ft_tablen(*tab);
		while (--i >= 0)
			free((*tab)[i]);
		free(*tab);
		*tab = NULL;
	}
}
