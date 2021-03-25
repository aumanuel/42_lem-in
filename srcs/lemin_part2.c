/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:51:36 by amanuel           #+#    #+#             */
/*   Updated: 2019/01/30 16:32:01 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void				dis_is_da_wei(t_s *s)
{
	s->path = ft_memalloc((*s->dawei + 1) * 4);
	*s->path = --*s->dawei;
	s->path[*s->dawei] = s->end;
	while (--*s->dawei && !(s->i = 0))
		while (!s->path[*s->dawei] && ++s->i <= s->nbrooms)
			if (s->dawei[s->i] == *s->dawei + 1 && !(s->j = 0))
				while (!s->path[*s->dawei] && ++s->j <= *s->pipes[s->i - 1])
					if (s->pipes[s->i - 1][s->j] == s->path[*s->dawei + 1])
						s->path[*s->dawei] = s->i;
	s->i = 0;
	while (++s->i < *s->path)
		*s->pipes[s->path[s->i] - 1] = 0;
	s->multipath = (int**)ft_addarray((void***)&s->multipath, (void**)&s->path);
}

void					show_me_da_wei(t_s *s)
{
	s->dawei = ft_memalloc((1 + s->nbrooms + 1) * 4);
	*s->dawei = 1;
	s->dawei[s->start] = *s->dawei;
	s->progress = 1;
	while (!s->solution && s->progress && !(s->progress = 0) && ++*s->dawei
			&& !(s->i = 0))
		while (!s->solution && ++s->i <= s->nbrooms)
			if (s->dawei[s->i] == *s->dawei - 1
					&& (s->j = *s->pipes[s->i - 1] + (1)))
				while (!s->solution && --s->j)
					if (!s->dawei[s->pipes[s->i - 1][s->j]]
						&& (s->dawei[s->pipes[s->i - 1][s->j]] = *s->dawei)
							&& ++s->progress
							&& s->pipes[s->i - 1][s->j] == s->end)
						s->solution = 1;
	if (s->solution && --*s->pipes[s->end - 1] >= 0)
		dis_is_da_wei(s);
	free(s->dawei);
}

static void				parsing_pipe(t_s *s, char **line)
{
	if (!s->pipes && (s->nbrooms = ft_tablen((void**)s->rooms)))
		s->pipes = (int**)ft_tabnew(s->nbrooms + 1, s->nbrooms + 1, 32);
	if (((!s->start || (s->start == s->ydt - (s->srtend + 1) && !(s->start = 0))
		|| !s->end || (s->end == s->ydt - (s->srtend + 1) && !(s->end = 0)))
		&& error(s, line, 2))
		|| ((!(ft_strchr(*line, '-')
		&& (s->i = ft_strchr(*line, '-') - *line))
		&& error(s, line, 8))))
		return ;
	s->solution = 0;
	s->j = 0 + (-1);
	while (!s->solution && s->rooms[++s->j])
		if (!ft_strncmp(*line, s->rooms[s->j], s->i - 1) && (s->k = 0 + (-1)))
			while (!s->solution && s->rooms[++s->k])
				if (!ft_strcmp(*line + s->i + 1, s->rooms[s->k]))
					s->solution = 1;
	if (s->solution)
	{
		++*s->pipes[s->j];
		s->pipes[s->j][*s->pipes[s->j]] = s->k + 1;
		++*s->pipes[s->k];
		s->pipes[s->k][*s->pipes[s->k]] = s->j + 1;
	}
	else
		error(s, line, 8);
}

static void				parsing_room(t_s *s, char **line)
{
	if (ft_strchr(*line, ' '))
	{
		if (s->pipes && error(s, line, 6))
			return ;
		s->i = ft_strchr(*line, ' ') - *line;
		if ((s->j = ft_isint(*line + s->i + 1, 32))
				&& (*line)[s->i + 1 + s->j] == ' '
				&& (s->k = ft_isint(*line + s->i + 1 + s->j + 1, 32))
				&& !(*line)[s->i + 1 + s->j + 1 + s->k])
		{
			s->buff = ft_strndup(*line, s->i);
			s->i = 0 + (-1);
			while (s->rooms && s->buff && s->rooms[++s->i])
				if (!ft_strcmp(s->buff, s->rooms[s->i]) && error(s, line, 7))
					ft_memdel((void**)&s->buff);
			s->rooms = (char**)ft_addarray((void***)&s->rooms,
						(void**)&s->buff);
		}
		else
			error(s, line, 3);
	}
	else
		parsing_pipe(s, line);
}

char					parsing(t_s *s, char **line)
{
	if (**line == '#')
	{
		if (!ft_strcmp("##start", *line) && (!s->start || !error(s, line, 4)))
			s->start = s->ydt - ++s->srtend;
		else if (!ft_strcmp("##end", *line) && (!s->end || !error(s, line, 5)))
			s->end = s->ydt - ++s->srtend;
		else if (s->ydt--)
			ft_memdel((void**)line);
	}
	else if (!s->ants)
	{
		if (!((s->k = ft_isint(*line, 32))
				&& !(*line)[s->k]
				&& **line != '-'
				&& (s->ants = ft_atoi(*line)) > 0))
			error(s, line, 1);
	}
	else
		parsing_room(s, line);
	return (1);
}
