/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:51:36 by amanuel           #+#    #+#             */
/*   Updated: 2019/03/12 02:48:29 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <unistd.h>

static void				end(t_s *s)
{
	if (s->bonus_actif && s->multipath)
	{
		ft_printf("\n=======STATS=======\n");
		ft_printf(" 🐜  %d fourmis\n", s->ants);
		ft_printf(" 🚪  %d rooms\n", s->nbrooms);
		ft_printf(" 📏  %d pipes\n",
				ft_tablen((void**)s->data) - s->nbrooms - 3);
		ft_printf(" 🛤  %d chemins\n", ft_tablen((void**)s->multipath));
		ft_printf(" ⛳  %d etapes\n", s->n - 1);
		ft_printf("===================\n");
	}
	if (s->data)
		ft_freetab((void***)&s->data);
	if (s->rooms)
		ft_freetab((void***)&s->rooms);
	if (s->pipes)
		ft_freetab((void***)&s->pipes);
	if (s->multipath)
		ft_freetab((void***)&s->multipath);
	if (s->p)
		ft_freetab((void***)&s->p);
	free(s);
}

static void				behavior_choice(t_s *s, char **line)
{
	ft_printf("%s\n", *line);
	ft_memdel((void**)line);
	ft_printf("Ignorer la ligne et continuer ? (yes, no, maybe)\n");
	get_next_line(1, line);
	if (line && *line && **line == 'm')
	{
		ft_memdel((void**)line);
		ft_printf("Choisis yes ou no !\n");
		get_next_line(1, line);
		ft_memdel((void**)line);
		ft_printf("Bon tu m'as saoule !\n");
		s->run = 0;
	}
	else if (line && *line && **line != 'y')
		s->run = 0;
	ft_memdel((void**)line);
}

char					error(t_s *s, char **line, char errno)
{
	if (s->bonus_actif)
	{
		if (errno == 1)
			ft_printf("ERROR: pas de fourmis\n");
		else if (errno == 2)
			ft_printf("ERROR: pas de paire start/end\n");
		else if (errno == 3 && !(s->ants = 0))
			ft_printf("ERROR: coordonnee room invalide\n");
		else if (errno == 4)
			ft_printf("ERROR: plusieurs start\n");
		else if (errno == 5)
			ft_printf("ERROR: plusieurs end\n");
		else if (errno == 6)
			ft_printf("ERROR: declaration de room dans les pipes\n");
		else if (errno == 7 && --s->ydt)
			ft_printf("ERROR: declaration d'une unique room deux fois\n");
		else if (errno == 8)
			ft_printf("ERROR: pipe invalide\n");
	}
	if (!s->bonus_actif || errno <= 3)
		s->run = 0;
	else
		behavior_choice(s, line);
	return (1);
}

static void				print_mi_da_wei(t_s *s)
{
	s->i = s->ants;
	s->j = ft_tablen((void**)s->multipath);
	s->p = (int**)ft_tabnew(s->j, 0, 0);
	s->k = 0 + (-1);
	while (s->multipath[++s->k])
		s->p[s->k] = (int*)ft_memalloc((*s->multipath[s->k] + 2) * 4);
	while (--s->i >= 0 && ++**s->p && !(s->k = 0))
		while (++s->k < s->j)
			if (*s->p[s->k - 1] + *s->multipath[s->k - 1]
			> *s->p[s->k] + *s->multipath[s->k] && s->i--)
				++*s->p[s->k];
	s->m = 1;
	while (s->m && !(s->m = 0)
				&& (s->k = 0 + (-1)) && ++s->n)
	{
		while (++s->k < s->j && (s->i = *s->multipath[s->k] + 1))
			while (--s->i)
				if ((s->i > 1 && (s->p[s->k][s->i] = s->p[s->k][s->i - 1]))
				|| (s->i == 1 && *s->p[s->k] && (*s->p[s->k])--
				&& ++s->l && (s->p[s->k][1] = s->l))
				|| (s->i == 1 && (s->p[s->k][1] = 0)))
					s->m += ft_printf("L%d-%s ", s->p[s->k][s->i],
						s->rooms[s->multipath[s->k][s->i] - 1]);
		ft_printf("\n");
	}
}

int						main(void)
{
	t_s					*s;
	char				*line;

	s = (t_s*)ft_memalloc(sizeof(t_s));
	s->bonus_actif = 1;
	s->run = 1;
	while (s->run && get_next_line(0, &line) > 0
				&& ++s->ydt && parsing(s, &line))
		s->data = (char**)ft_addarray((void***)&s->data, (void**)&line);
	if (s->start && s->end && s->rooms && s->pipes && (s->solution = 1))
		while (s->solution && !(s->solution = 0) && *s->pipes[s->end - 1])
			show_me_da_wei(s);
	if (s->multipath || (!s->bonus_actif && !ft_printf("ERROR\n")))
	{
		ft_puttab(s->data);
		ft_printf("\n");
		print_mi_da_wei(s);
	}
	else if (s->bonus_actif && s->ants && s->start && s->end)
		ft_printf("ERROR: pas de solution\n");
	else if (s->bonus_actif && !s->ydt)
		ft_printf("ERROR: fichier vide\n");
	end(s);
	return (0);
}
