/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:51:26 by amanuel           #+#    #+#             */
/*   Updated: 2019/03/12 01:46:24 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"

typedef struct		s_s
{
	char			bonus_actif;
	char			run;
	int				ydt;
	char			srtend;
	int				i;
	int				j;
	int				k;
	int				l;
	int				m;
	int				n;
	int				solution;
	int				progress;
	int				ants;
	int				start;
	int				end;
	int				nbrooms;
	char			**data;
	char			**rooms;
	int				**pipes;
	char			*buff;
	int				*dawei;
	int				*path;
	int				**multipath;
	int				**p;
}					t_s;

char				parsing(t_s *s, char **line);
void				show_me_da_wei(t_s *s);
char				error(t_s *s, char **line, char errno);

#endif
